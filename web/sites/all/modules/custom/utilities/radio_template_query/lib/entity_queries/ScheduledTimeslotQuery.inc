<?php
require_once dirname(__DIR__) . '/utilities/Helpers.inc';


class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  protected function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }


  protected function stream($stream) {
    $this->fieldCondition('field_show', 'target_id', $stream, '=');
    return $this;
  }


  protected function sortByTimeslot() {
    $this->addTag('radio_ScheduledTimeslotQuery_orderByTimeslot');
  }


  protected function timeslotIsAfter($timestamp) {
    $this->dateFieldIsAfter('field_timeslot', $timestamp);
  }


  public function getNow() {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetNow');
    return $this;
  }


  public function getNext($count = NULL) {
    $now = time();
    $this->timeslotIsAfter($now);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot();
    return $this;
  }


  public function getRange($start, $finish) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetRange');
    $this->addTag("parameter_ScheduledTimeslotQuery__{$start}__{$finish}");
    return $this;
  }


  public static function modifyGetNow(QueryAlterableInterface $query) {
    $now = time();
    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldOccurring($query, 'field_timeslot', $now, $now);
  }


  public static function modifyGetRange(QueryAlterableInterface $query) {
    $start = $end = time();
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, 'parameter_ScheduledTimeslotQuery')) {
        $parts = explode('__', $tag);
        $start = $parts[1];
        $finish = $parts[2];
        break;
      }
    }

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldInRange($query, 'field_timeslot', $start, $finish);
    NodeQuery::sortField($query, 'field_timeslot');
  }

  public static function orderByTimeslot(QueryAlterableInterface $query) {
    $query->orderBy('field_data_field_timeslot0.field_timeslot_value', 'ASC');
  }
}
