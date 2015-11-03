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
    $schedule = $this->getUpcomingSchedule($stream, $count);

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
      $start = $episode->field_air_time->value();

      if (!$this->withinAnHour($start)) {
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
  private function getUpcomingSchedule($stream, $count) {
    $now = time();
    $schedule = [];

    $query = new ScheduledTimeslotQuery();
    $query->getNext($stream, $count);
    $result = $query->execute();

    if (empty($result)) {
      return [];
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
    $wrapped = entity_metadata_wrapper('node', $item->nid);
    return $wrapped;
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