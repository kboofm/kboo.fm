<?php

class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }

  public function getNow() {
    $now = now();

    # where
    $this->fieldCondition('field_timeslot', 'value', $now, '<=');
    $this->fieldCondition('field_timeslot', 'value2', $now, '>=');

    return $this;
  }
}
