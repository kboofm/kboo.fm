<?php

class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }

  public function getNow() {
    return $this;
  }
}
