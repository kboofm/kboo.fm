<?php

class ScheduledTimeslotContentType {

  /**
   * Check if timeslot is already scheduled
   *
   * @param $node
   * @return bool
   */
  public static function isScheduled($node) {
    $stream_id = $node->field_stream['und'][0]['target_id'];
    $timeslots = $node->field_timeslot['und'];
    $initial_start_time = strtotime("+1 minute", $timeslots[0]['value']);

    $query = new ScheduledTimeslotQuery();
    $query->getAt(
      $stream_id,
      $initial_start_time
    );

    if ($node->nid) {
      $query->excludeNodes($node->nid);
    }

    $result = $query->execute();

    return !empty($result);
  }
}
