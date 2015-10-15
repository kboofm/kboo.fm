<?php
require_once dirname(__DIR__) . '/utilities/Helpers.inc';


class StationContentQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'station_content';
  }

  public function getEpisode($start, $finish) {
    $this->addTag('radio_StationContentQuery_modifyGetEpisode');
    $this->addTag("parameter_StationContentQuery__{$start}__{$finish}");
    return $this;
  }

  public static function modifyGetEpisode(QueryAlterableInterface $query) {
    $start = $finish = time();
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, 'parameter_StationContentQuery')) {
        $parts = explode('__', $tag);
        $start = $parts[1];
        $finish = $parts[2];
        break;
      }
    }

    NodeQuery::joinField($query, 'field_air_time');
    NodeQuery::dateFieldEquals($query, 'field_air_time', $start, $finish);
  }
}
