<?php

class StationContentComponent extends BaseComponent {

  public function latestAudio() {
    $query = new StationContentQuery();
    $query->latestAudio();
    $result = $query->execute();

    $processor = new ListProcessor();
    return $processor->process(
      $this->getNids($result)
    );
  }


  public function getContentForProgram(
    $program_nid,
    $page = 1,
    $per_page = 10
  ) {

    $start = ($page - 1) * $per_page;

    $query = new StationContentQuery();
    $query = $query->getContentByProgram($program_nid);
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $episodes = array_values(
      node_load_multiple($nids)
    );

    $query = new StationContentQuery();
    $query = $query->getContentByProgram($program_nid);
    $query->range($start, $per_page);
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $episodes;
    return $pager;
  }


   /**
   * Get upcoming episode nodes, create as needed
   *
   * @param $stream
   * @param $count
   * @return array
   */
  public function getRippingEpisodes($stream, $count) {
    $schedule = $this->getRippingSchedule($stream, $count);

    $terms = taxonomy_get_term_by_name(
      'Episode',
      'station_content_types'
    );
    $episode_term = reset($terms);

    foreach ($schedule as &$schedule_item) {
      if ($schedule_item['episode']) {
        continue;
      }

      if (!$schedule_item['timeslot_program']) {
        continue;
      }

      $this->createEpisode($schedule_item, $episode_term);
    }

    // get an array of episode nodes
    $episodes = array_map(
      function ($item) {
        return $item['episode'];
      },
      $schedule
    );

    // filter out any null entries
    $episodes = array_filter($episodes);

    return $episodes;
  }


  private function getEpisodeNidFromRipFilename($ripfile) {
    // $ripfile format: /path/kboo_episode.2.140320.1130.3501.1.mp3
    // The last number before .mp3 is the episode nid

    $parts = explode('.', $ripfile);
    end($parts);
    return prev($parts);
  }


  private function getRippedFilenames() {
    $ripdir = variable_get(
      'radio_station_rip_filepath',
      '/tmp'
    );

    if (!Helpers::endsWith($ripdir, '/')) {
      $ripdir .= '/';
    }

    $filenames = glob("{$ripdir}*.mp3");
    return $filenames;
  }


  public function attachNewRips() {
    foreach ($this->getRippedFilenames() as $rip_filepath) {
      $episode_nid = $this->getEpisodeNidFromRipFilename($rip_filepath);
      $wrapped_episode = entity_metadata_wrapper('node', $episode_nid);

      // http://stackoverflow.com/a/5141484/2407209
      $ripped_file = (object) [
        'uid' => 1,
        'uri' => $rip_filepath,
        'filemime' => file_get_mimetype($rip_filepath),
        'status' => 1,
        'display' => 1,
      ];

      $destination = variable_get(
        'radio_station_rip_destination',
        'episode_audio'
      );

      if (!Helpers::endsWith($destination, '/')) {
        $destination .= '/';
      }

      $basename = basename($rip_filepath);
      $file = file_move(
        $ripped_file,
        "public://{$destination}{$basename}"
      );

      // http://drupal.stackexchange.com/a/69545
      $file_wrapper = [(array)$file];
      $wrapped_episode->field_audio_files->set($file_wrapper);
      $wrapped_episode->save();
    }
  }


  private function getEpisodesToCull() {
    $now_minus_twoweeks = strtotime('-2 weeks', time());
    $query = new StationContentQuery();
    $query->type('Episode');
    $query->olderThan($now_minus_twoweeks);
    $query->hasAudio();
    $result = $query->execute();

    $episodes = [];
    if (empty($result)) {
      return $episodes;
    }

    foreach ($result['node'] as $nid => $item) {
      $episodes[] = entity_metadata_wrapper('node', $nid);
    }

    return $episodes;
  }


  public function cullArchive() {
    $episodes = $this->getEpisodesToCull();
    foreach ($episodes as $episode) {
      foreach ($episode->field_audio_files as $audio_file) {
        $file_object = (object) $audio_file->value();
        file_delete($file_object);
      }
      $episode->field_audio_files->set([]);
      $episode->save();
    }
  }


  public function scheduleRippingEpisodes($episodes) {
    foreach ($episodes as $episode) {
      $air_time = $episode->field_air_time->value();

      if (!$this->withinAnHour($air_time['value'])) {
        continue;
      }

      $recording_type = $episode->field_episode_record->value();
      if ($recording_type == EArchiveTypes::NEVER) {
        continue;
      }

      $this->queueEpisodeRip($episode);
    }
  }


  private function queueEpisodeRip($episode) {
    /* StreamRipper options
      -l : length in seconds
      -a filename : rip to single file; timestamp if no filename
      -A don't write individual tracks
      -q : add sequence number
      -s : don't create stream dir
      -d directory : destination dir
      --quiet : no output
    */

    $recording_type = $episode->field_episode_record->value();
    $air_time = $episode->field_air_time->value();
    $date = date('ymd.Hi', $air_time['value']);
    $ripper = variable_get(
      'radio_station_streamripper',
      '/usr/bin/streamripper'
    );

    $program_nid = 'none';
    $programs = $episode->field_produced_for;
    if ($programs && isset($programs[0])) {
      $program_nid = $programs[0]->getIdentifier();
    }

    // start one minute early, end one minute late
    $padding = 60;
    $start = $air_time['value'] - $padding;
    $length = $air_time['value2'] + $padding - $start;
    $atd_time = date('H:i', $start);
    $episode_nid = $episode->getIdentifier();
    $filename = "kboo_episode.{$recording_type}.{$date}.{$program_nid}.{$episode_nid}.mp3";

    $ripdir = variable_get('radio_station_rip_filepath', '/tmp');
    $stream = variable_get(
      'radio_station_rip_stream',
      'http://listen.kboo.fm:8000/high.m3u'
    );

    $directory_accessible = file_prepare_directory(
      $ripdir,
      $mode = FILE_CREATE_DIRECTORY
    );

    if (!$directory_accessible) {
      return;
    }

    $command = "$ripper {$stream}";
    $command .= "-l {$length} -A -a {$filename} -q -s -d {$ripdir} --quiet";
    $command .= "; rm {$ripdir}/{$filename}.cue";
    $command = "echo \"{$command}\" | at {$atd_time}";
    shell_exec($command);

    watchdog(
      "radio_station",
      "Executed: {$command}",
      WATCHDOG_INFO
    );
  }


  private function withinAnHour($timestamp) {
    $now = time();
    $an_hour_from_now = strtotime('+1 hour', $now);
    return ($now < $timestamp && $timestamp <= $an_hour_from_now);
  }


  /**
   * Create an episode node
   *
   * @param $schedule_item
   * @param $episode_term
   * @throws \Exception
   */
  private function createEpisode(&$schedule_item, $episode_term) {
    $program = $schedule_item['timeslot_program'];
    $date = date('m/d/y', $schedule_item['start']);

    $node = new stdClass();
    $node->title = "{$program->title->value()} on {$date}";
    $node->type = 'station_content';

    node_object_prepare($node);

    $lang = LANGUAGE_NONE;
    $node->language = $lang;
    $node->uid = 1;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 0;

    // field_station_content
    $node->field_station_content_type[$lang][] = [
      'tid' => $episode_term->tid
    ];


    // field_air_time
    $node->field_air_time[$lang][] = [
      'value' => $schedule_item['start'],
      'value2' => $schedule_item['finish'],
    ];


    // field_produced_for
    $node->field_produced_for[$lang][] = [
      'target_id' => $program->getIdentifier(),
    ];


    // field_hosted_by
    foreach ($program->field_hosted_by->value() as $show_host ) {
      $node->field_hosted_by[$lang][] = [
        'target_id' => $show_host->nid,
      ];
    }

    // field_short_description
    $node->field_short_description[$lang][] = [
      'value' => $program->field_short_description->value(),
    ];


    // field_episode_record
    $value = $program->field_episode_record->value();
    $value = is_null($value) ? 0 : $value;

    $node->field_episode_record[$node->language][] = [
      'value' => $value,
    ];

    node_save($node);
    $schedule_item['episode'] = entity_metadata_wrapper('node', $node);
  }


  /**
   * Get the upcoming schedule
   *
   * @param $stream
   * @param $count
   * @return array
   */
  private function getRippingSchedule($stream, $count) {
    $now = time();
    $end = strtotime("+25 hours", $now);
    $schedule = [];

    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $now, $end);
    $result = $query->execute();

    if (empty($result)) {
      return $schedule;
    }

    foreach ($result['node'] as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $now) {
          continue;
        }

        $schedule[] = $this->buildScheduleItem($wrapped, $timeslot);
      }
    }

    usort(
      $schedule,
      function ($a, $b) {
        return $a['start'] - $b['start'];
      }
    );

    return array_slice($schedule, 0, $count);
  }


  /**
   * Check if episode exists for a timeslot
   *
   * @param $timeslot
   * @return bool
   */
  private function getEpisode($timeslot) {
    $query = new StationContentQuery();
    $query->getEpisode(
      $timeslot['value'],
      $timeslot['value2']
    );
    $result = $query->execute();

    if (empty($result)) {
      return null;
    }

    $item = reset($result['node']);
    return entity_metadata_wrapper('node', $item->nid);
  }


  /**
   * Get a program for a timeslot
   *
   * @param $wrapped_scheduled_timeslot
   * @return null
   */
  private function getTimeslotProgram($wrapped_scheduled_timeslot) {
    try {
      return $wrapped_scheduled_timeslot->field_show;
    } catch (EntityMetadataWrapperException $e) {
      return NULL;
    }
  }


  /**
   * Build schedule item array
   *
   * @param $wrapped_scheduled_timeslot
   * @param $timeslot
   * @return array
   */
  private function buildScheduleItem($wrapped_scheduled_timeslot, $timeslot) {
    $program = NULL;
    $episode = $this->getEpisode($timeslot);

    if (!$episode) {
      $program = $this->getTimeslotProgram($wrapped_scheduled_timeslot);
    }

    $schedule_item = [
      'episode' => $episode,
      'start' => $timeslot['value'],
      'finish' => $timeslot['value2'],
      'timeslot_program' => $program,
    ];

    return $schedule_item;
  }

}
