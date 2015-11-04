<?php
require_once dirname(__DIR__) . '/utilities/Helpers.inc';


class StationContentQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'station_content';
  }


  public function getEpisode($start, $end) {
    $this->type('Episode');
    $this->fieldCondition('field_air_time', 'value', $start, '=', 0);
    $this->fieldCondition('field_air_time', 'value2', $end, '=', 0);
    return $this;
  }


  public function olderThan($timestamp) {
    $this->fieldCondition('field_air_time', 'value', $timestamp, '<=');
    return $this;
  }


  public function type($term_name) {
    $terms = taxonomy_get_term_by_name($term_name, 'station_content_types');
    $term = reset($terms);

    $tid = NULL;
    if (isset($term->tid)) {
      $tid = $term->tid;
    }

    $this->fieldCondition('field_station_content_type', 'tid', $tid);
    return $this;
  }
}
