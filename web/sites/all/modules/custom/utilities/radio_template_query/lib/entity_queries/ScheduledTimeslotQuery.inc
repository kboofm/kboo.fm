<?php

class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }


  public function stream($stream) {
    # where
    $this->fieldCondition('field_show', 'target_id', $stream, '=');

    return $this;
  }


  public function getNow() {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetNow');

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


  public static function modifyGetNow(QueryAlterableInterface $query) {
    $now = time();

    $query->join(
      'field_data_field_timeslot',
      'timeslot',
      'node.nid = timeslot.entity_id'
    );

    $query->condition(db_and()
      ->condition('timeslot.field_timeslot_value', $now, '<=')
      ->condition('timeslot.field_timeslot_value2', $now, '>=')
    );
  }
}
