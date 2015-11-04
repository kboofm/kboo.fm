<?php
abstract class ArchiveTypes {
  const NEVER = 0;
  const TEMPORARY = 1;
  const PERMANENT = 2;
}


class RadioStation {
  private $episode_term;


  /**
   * Constructor
   */
  public function __construct() {
    $terms = taxonomy_get_term_by_name(
      'Episode',
      'station_content_types'
    );

    $this->episode_term = reset($terms);
  }


  /**
   * Create upcoming upisode nodes
   *
   * @param $stream
   * @param $count
   * @return array
   */
  public function createNextEpisodes($stream, $count) {
    $schedule = $this->getUpcomingCronSchedule($stream, $count);

    foreach ($schedule as &$schedule_item) {
      if ($schedule_item['episode']) {
        continue;
      }

      if (!$schedule_item['program']) {
        continue;
      }

      $this->createEpisode($schedule_item);
    }

    $episodes = array_map(
      function ($item) {
        return $item['episode'];
      },
      $schedule
    );

    $episodes = array_filter($episodes);

    return $episodes;
  }


  public function scheduleRippingEpisodes($episodes) {
    foreach ($episodes as $episode) {
      $air_time = $episode->field_air_time->value();

      if (!$this->withinAnHour($air_time['value'])) {
        continue;
      }

      $recording_type = $episode->field_episode_record->value();
      if ($recording_type == ArchiveTypes::NEVER) {
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
    $ripper = variable_get('radio_station_streamripper', '/usr/bin/streamripper');
    $date = date('ymd.Hi', $air_time['value']);
//    $program = $episode->field_related_program->value();
//    $filename = "kboo_episode.{$recording_type}.{$date}.{$program}.mp3";
    $filename = "kboo_episode.{$recording_type}.{$date}.mp3";

    // start one minute early, end one minute late
    $padding = 60;
    $start = $air_time['value'] - $padding;
    $length = $air_time['value2'] + $padding - $start;
    $atd_time = date('H:i', $start);

    $record_dir = variable_get('radio_station_rip_filepath', '/tmp');
    $stream = variable_get(
      'radio_station_rip_stream',
      'http://listen.kboo.fm:8000/high.m3u'
    );

    $directory_accessible = file_prepare_directory(
      $record_dir,
      $mode = FILE_CREATE_DIRECTORY
    );

    if (!$directory_accessible) {
      return;
    }

    $temporary = ($recording_type == ArchiveTypes::TEMPORARY);
    $rip_length = (5 * 3600) + ($padding * 2);
    $length_check = ($length < $rip_length);

    if ($temporary && $length_check) {
      $length = $rip_length;
    }

    $command = "$ripper {$stream}";
    $command .= "-l {$length} -A -a {$filename} -q -s -d {$record_dir} --quiet";
    $command .= "; rm {$record_dir}/{$filename}.cue";
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
   * @throws \Exception
   */
  private function createEpisode(&$schedule_item) {
    $program = $schedule_item['program'];
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
      'tid' => $this->episode_term->tid
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
  private function getUpcomingCronSchedule($stream, $count) {
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
      'program' => $program,
    ];

    return $schedule_item;
  }
}