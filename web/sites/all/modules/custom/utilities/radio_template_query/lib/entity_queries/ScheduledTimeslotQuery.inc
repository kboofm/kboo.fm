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


  protected function sortByTimeslot($direction = 'ASC') {
    $this->addTag('radio_ScheduledTimeslotQuery_orderByTimeslot');
    $this->addTag("parameter_ScheduledTimeslotQuery__{$direction}");
  }


  protected function timeslotIsAfter($timestamp) {
    $this->dateFieldIsAfter('field_timeslot', $timestamp);
  }


  protected function timeslotIsBefore($timestamp) {
    $this->dateFieldIsBefore('field_timeslot', $timestamp);
  }


  public function getNow() {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetNow');
    return $this;
  }


  public function getNext($timestamp, $count = 1) {
    $this->timeslotIsAfter($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot();
    return $this;
  }


  public function getPrevious($timestamp, $count = 1) {
    $this->timeslotIsBefore($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot('DESC');
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

  private static function getParameters(QueryAlterableInterface $query) {
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, 'parameter_ScheduledTimeslotQuery')) {
        return explode('__', $tag);
      }
    }

    return NULL;
  }

  public static function modifyGetRange(QueryAlterableInterface $query) {
    $start = $end = time();
    $params = ScheduledTimeslotQuery::getParameters($query);

    if ($params) {
      $start = $params[1];
      $finish = $params[2];
    }

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldInRange($query, 'field_timeslot', $start, $finish);
    NodeQuery::sortField($query, 'field_timeslot');
  }

  public static function orderByTimeslot(QueryAlterableInterface $query) {
    $params = ScheduledTimeslotQuery::getParameters($query);
    $direction = 'ASC';

    if ($params) {
      $direction = $params[0];
    }

    $query->orderBy('field_data_field_timeslot0.field_timeslot_value', $direction);
  }
}
