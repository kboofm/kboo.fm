<?php

class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }

  public function getNow() {
    $now = time();

    # where
    $this->fieldCondition('field_timeslot', 'value', $now, '<=');
    $this->fieldCondition('field_timeslot', 'value2', $now, '>=');

    return $this;
  }

  public function getNext($count) {
    $now = time();

    # where
    $this->fieldCondition('field_timeslot', 'value', $now, '>');

    # limit
    $this->setLimit($count);

    # order by
    $this->fieldOrderBy('field_timeslot', 'value', 'ASC');

    return $this;
  }
}
