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

    $query = new ScheduledTimeslotQuery();
    $query->getAnyAt(
      $stream_id,
      $timeslots
    );

    if ($node->nid) {
      $query->excludeNodes($node->nid);
    }

    $result = $query->execute();

    return !empty($result);
  }
}
