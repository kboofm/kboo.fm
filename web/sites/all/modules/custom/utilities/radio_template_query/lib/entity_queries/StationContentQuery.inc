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
    $this->addTag('radio_StationContentQuery_modifyGetEpisode');
    $this->addTag("parameter_StationContentQuery__{$start}__{$end}");
    return $this;
  }

  public static function modifyGetEpisode(QueryAlterableInterface $query) {
    $start = $end = time();
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, 'parameter_StationContentQuery')) {
        $parts = explode('__', $tag);
        $start = $parts[1];
        $end = $parts[2];
        break;
      }
    }

    $query->join(
      'field_data_field_air_time',
      'air_time',
      'node.nid = air_time.entity_id'
    );

    $query->condition(db_and()
      ->condition('air_time.field_air_time_value', $start, '=')
      ->condition('air_time.field_air_time_value2', $end, '=')
    );
  }
}
