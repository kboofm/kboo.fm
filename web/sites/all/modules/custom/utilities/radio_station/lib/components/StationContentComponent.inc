<?php

class StationContentComponent extends BaseComponent {

  public function getAudio($page) {
    $per_page = 10;
    $start = ($page - 1) * $per_page;

    $query = new StationContentQuery();
    $query->getAudio();
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    $query = new StationContentQuery();
    $query->getAudio();
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $events;
    return $pager;
  }


  public function getAudioFeed() {
    $query = new StationContentQuery();
    $query->getAudio();
    $query->range(0, 10);
    $result = $query->execute();
    return $this->getNids($result);
  }


  public function latestAudio($count) {
    $cache_key = "radio_station_latest_audio";
    $cache_table = "cache_radio_station";

    $loaded = false;
    if ($cache = cache_get($cache_key, $cache_table)) {
      $data = $cache->data;

      if ($data['requested'] >= $count) {
        $episodes = array_slice($data['episodes'], 0, $count);
        $loaded = true;
      }
    }

    if (!$loaded) {
      $query = new StationContentQuery();
      $query->getAudio($count);
      $result = $query->execute();

      $processor = new StationContentProcessor();
      $episodes = $processor->process(
        $this->getNids($result)
      );

      $data = [
        'episodes' => $episodes,
        'requested' => $count,
      ];

      cache_set($cache_key, $data, $cache_table);
    }
    
    return $episodes;
  }


  public function latestPlaylists($count) {
    $cache_key = "radio_station_latest_playlists";
    $cache_table = "cache_radio_station";

    if ($cache = cache_get($cache_key, $cache_table)) {
      $data = $cache->data;

      if ($data['requested'] >= $count) {
        $playlists = array_slice($data['playlists'], 0, $count);
        return $playlists;
      }
    }

    $spinitron_data = RadioSpinitron::getLatestPlaylists($count);

    $episodes = array_map(
      function ($item) {
        $onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = strtotime($onair);

        $offair = "{$item['PlaylistDate']} {$item['OffairTime']}";
        $offair = strtotime($offair);

        if ($offair < $onair) {
          // If offair is the next day, then playlist date will be one day off
          $offair = strtotime("+1 day", $offair);
        }

        $query = new StationContentQuery();
        $query->getEpisodeInRange($onair, $offair);
        $result = $query->execute();
        $nids = $this->getNids($result);

        if ($nids) {
          return $nids[0];
        }
        else {
          return NULL;
        }
      },
      $spinitron_data
    );

    $episodes = array_filter($episodes);
    $episodes = array_values($episodes);
    $episodes = array_slice($episodes, 0, $count);

    $processor = new StationContentProcessor();
    $playlists = $processor->process($episodes);

    $data = [
      'playlists' => $playlists,
      'requested' => $count,
    ];

    cache_set($cache_key, $data, $cache_table);
    return $playlists;
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
    $nids = $this->getNids($result);

    $episodes = array_values(
      node_load_multiple($nids)
    );

    $query = new StationContentQuery();
    $query->getContentByProgram($program_nid);
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $episodes;
    return $pager;
  }


  public function getUpcomingForProgram($program_nid, $count) {
    $query = new StationContentQuery();
    $query->getUpcomingByProgram($program_nid, $count);
    $result = $query->execute();

    $processor = new StationContentProcessor();
    return $processor->processUpcoming(
      $this->getNids($result)
    );
  }


  public function getPodcast($target, $type) {
    switch ($type) {
      case "genre":
        return $this->getPodcastForGenre($target);
      case "person_profile":
        return $this->getPodcastForProfile($target);
      case "program":
        return $this->getPodcastForProgram($target);
      case "topic":
        return $this->getPodcastForTopic($target);
      default:
        return [];
    }
  }


  private function getPodcastForGenre($target) {
    $query = new StationContentQuery();
    $query = $query->getPodcastByGenre($target);
    $result = $query->execute();
    return $this->getNids($result);
  }


  private function getPodcastForTopic($target) {
    $query = new StationContentQuery();
    $query = $query->getPodcastByTopic($target);
    $result = $query->execute();
    return $this->getNids($result);
  }


  private function getPodcastForProgram($target_nid) {
    $query = new StationContentQuery();
    $query = $query->getPodcastByProgram($target_nid);
    $result = $query->execute();

    $processor = new PodcastProcessor();
    return $processor->process(
      $this->getNids($result)
    );
  }


  private function getPodcastForProfile($target_nid) {
    $query = new StationContentQuery();
    $query = $query->getPodcastByProfile($target_nid);
    $result = $query->execute();
    return $this->getNids($result);
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
      if ($recording_type == EArchiveTypes::Never) {
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
    $timeslots = [];

    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $now, $end);
    $result = $query->execute();

    if (empty($result)) {
      return $schedule;
    }

    foreach ($result['node'] as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $entity_timeslots = $entity->field_timeslot->value();

      $entity_timeslots = array_map(
        function ($timeslot) use ($entity, $now, $end) {
          if ($timeslot['value'] <= $now || $timeslot['value'] >= $end) {
            return false;
          }

          $timeslot['entity'] = $entity;
          return $timeslot;
        },
        $entity_timeslots
      );

      $entity_timeslots = array_filter($entity_timeslots);
      $timeslots = array_merge($timeslots, $entity_timeslots);
    }

    usort(
      $timeslots,
      function ($a, $b) {
        return $a['value'] - $b['value'];
      }
    );

    $timeslots = array_slice($timeslots, 0, $count);

    $schedule = array_map(
      function ($timeslot) {
        $entity = $timeslot['entity'];
        return $this->buildScheduleItem($entity, $timeslot);
      },
      $timeslots
    );

    return $schedule;
  }


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
      try {
        $program = $wrapped_scheduled_timeslot->field_show;
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }
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
