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
    $this->addTag("parameter_ScheduledTimeslotQuery_direction__{$direction}");
  }


  protected function timeslotIsAfter($timestamp) {
    $this->dateFieldIsAfter('field_timeslot', $timestamp);
  }


  protected function timeslotIsBefore($timestamp) {
    $this->dateFieldIsBefore('field_timeslot', $timestamp);
  }


  protected function addStreamParameter($stream) {
    $stream_nid = ScheduledTimeslotQuery::getStreamNid($stream);
    $this->addTag('radio_ScheduledTimeslotQuery_addStream');
    $this->addTag("parameter_ScheduledTimeslotQuery_stream__{$stream_nid}");
  }


  public function getNow($stream) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetNow');
    $this->addStreamParameter($stream);
    return $this;
  }


  public function getNext($stream, $timestamp, $count = 1) {
    $this->addStreamParameter($stream);
    $this->timeslotIsAfter($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot();
    return $this;
  }


  public function getPrevious($stream, $timestamp, $count = 1) {
    $this->addStreamParameter($stream);
    $this->timeslotIsBefore($timestamp);

    if ($count) {
      $this->setLimit($count);
    }

    $this->sortByTimeslot('DESC');
    return $this;
  }


  public function getAt($stream, $timestamp) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetAt');
    $this->addTag("parameter_ScheduledTimeslotQuery_timestamp__{$timestamp}");
    $this->addStreamParameter($stream);
    return $this;
  }



  public function getRange($stream, $start, $end) {
    $this->addTag('radio_ScheduledTimeslotQuery_modifyGetRange');
    $this->addTag("parameter_ScheduledTimeslotQuery_daterange__{$start}__{$end}");
    $this->addStreamParameter($stream);
    return $this;
  }


  private static function getParameters(QueryAlterableInterface $query, $name) {
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, "parameter_ScheduledTimeslotQuery_{$name}")) {
        $parts = explode('__', $tag);
        array_shift($parts);

        $parts = array_map(
          function ($item) {
            return str_replace('___', ' ', $item);
          },
          $parts
        );

        return $parts;
      }
    }

    return NULL;
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
    $params = ScheduledTimeslotQuery::getParameters($query, 'stream');

    if ($params) {
      $stream = $params[0];
    } else {
      $stream = ScheduledTimeslotQuery::getStreamNid(Streams::One);
    }

    NodeQuery::joinField($query, 'field_stream');
    $query->condition("field_stream.field_stream_target_id", $stream, "=");
  }


  public static function modifyGetNow(QueryAlterableInterface $query) {
    $now = time();
    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldOccurring($query, 'field_timeslot', $now, $now);
  }


  public static function modifyGetAt(QueryAlterableInterface $query) {
    $timestamp = time();
    $params = ScheduledTimeslotQuery::getParameters($query, 'timestamp');

    if ($params) {
      $timestamp = $params[0];
    }

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldOccurring($query, 'field_timeslot', $timestamp, $timestamp);
  }


  public static function modifyGetRange(QueryAlterableInterface $query) {
    $start = $end = time();
    $params = ScheduledTimeslotQuery::getParameters($query, 'daterange');

    if ($params) {
      $start = $params[0];
      $end = $params[1];
    }

    NodeQuery::joinField($query, 'field_timeslot');
    NodeQuery::dateFieldInRange($query, 'field_timeslot', $start, $end);
    NodeQuery::sortField($query, 'field_timeslot');
  }


  public static function orderByTimeslot(QueryAlterableInterface $query) {
    $params = ScheduledTimeslotQuery::getParameters($query, 'direction');
    $direction = 'ASC';

    if ($params) {
      $direction = $params[0];
    }

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
