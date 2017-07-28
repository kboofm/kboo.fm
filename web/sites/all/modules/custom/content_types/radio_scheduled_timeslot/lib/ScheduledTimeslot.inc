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
	if(!empty($result['node']))
	{
		foreach($result['node'] as $res)
		{
			drupal_set_message('Node <a href="/node/' . $res->nid . '">' . $res->nid . '</a> is already scheduled in that timeslot.', 'warning');
		}
	}
    return !empty($result);
  }
}
