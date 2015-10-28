<?php
require_once dirname(__DIR__) . '/utilities/Helpers.inc';


class ScheduledTimeslotQuery extends NodeQuery {

  /**
   * Initialize
   */
  protected function initialize() {
    $this->content_type = 'scheduled_timeslot';
  }


  protected function sortByTimeslot($direction = 'ASC') {
    $this->addTag('radio_ScheduledTimeslotQuery_orderByTimeslot');
    NodeQuery::addParam('direction', $direction);
  }


  protected function timeslotIsAfter($timestamp) {
    $this->dateFieldIsAfter('field_timeslot', $timestamp);
  }


  protected function timeslotIsBefore($timestamp) {
    $this->dateFieldIsBefore('field_timeslot', $timestamp);
  }


  protected function whereStream($stream) {
    $stream_nid = ScheduledTimeslotQuery::getStreamNid($stream);
    $this->addTag('radio_ScheduledTimeslotQuery_addStream');
    NodeQuery::addParam('stream', $stream_nid);
  }


  public function getNow($stream) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetNow');
    $this->whereStream($stream);
    return $this;
  }


  public function getNext($stream, $timestamp, $count = 1) {
    $this->whereStream($stream);
    $this->timeslotIsAfter($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot();
    return $this;
  }


  public function getPrevious($stream, $timestamp, $count = 1) {
    $this->whereStream($stream);
    $this->timeslotIsBefore($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot('DESC');
    return $this;
  }


  public function getAt($stream, $timestamp) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetAt');
    NodeQuery::addParam('timestamp', $timestamp);
    $this->whereStream($stream);
    return $this;
  }


  public function getAnyAt($stream, array $timestamps) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetAnyAt');
    NodeQuery::addParam('timestamps', $timestamps);
    $this->whereStream($stream);
    return $this;
  }


  public function getRange($stream, $start, $end) {
    $daterange = [
      $start,
      $end
    ];

    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetRange');
    NodeQuery::addParam('daterange', $daterange);
    $this->whereStream($stream);
    return $this;
  }




  public static function getStreamNid($stream) {
    if (is_numeric($stream)) {
      return (int)$stream;
    }

    $query = new ProgramQuery();
    $query->getStreams($stream);
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    $stream_node = reset($result['node']);
    return $stream_node->nid;
  }


  public static function addStream(QueryAlterableInterface $query) {
    $default = ScheduledTimeslotQuery::getStreamNid(Streams::One);
    $stream = NodeQuery::getParam('stream', $default);

    NodeQuery::joinField($query, 'field_stream');
    $query->condition("field_stream.field_stream_target_id", $stream, "=");
  }


  public static function modifyGetNow(QueryAlterableInterface $query) {
    $now = time();
    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldOccurring($query, 'field_timeslot', $now, $now);
  }


  public static function modifyGetAt(QueryAlterableInterface $query) {
    $timestamp = NodeQuery::getParam('timestamp', time());
    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldOccurring($query, 'field_timeslot', $timestamp, $timestamp);
  }


  public static function modifyGetAnyAt(QueryAlterableInterface $query) {
    $timestamps = NodeQuery::getParam('timestamps');

    if (!$timestamps) {
      return;
    }

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldAnyOccurring($query, 'field_timeslot', $timestamps);
  }


  public static function modifyGetRange(QueryAlterableInterface $query) {
    $now = time();
    $default = [$now, $now];
    list($start, $end) = NodeQuery::getParam('daterange', $default);

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldInRange($query, 'field_timeslot', $start, $end);
    NodeQuery::sortField($query, 'field_timeslot');
  }


  public static function orderByTimeslot(QueryAlterableInterface $query) {
    $direction = NodeQuery::getParam('direction', 'ASC');
    $timeslot_table = 'field_data_field_timeslot0';
    $timeslot_field = 'field_timeslot_value';

    $query->addField(
      $timeslot_table,
      $timeslot_field,
      $timeslot_field
    );

    $query->orderBy("{$timeslot_table}.{$timeslot_field}", $direction);
  }
}
