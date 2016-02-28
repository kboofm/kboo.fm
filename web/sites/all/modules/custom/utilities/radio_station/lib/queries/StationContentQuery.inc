<?php
class StationContentQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = "station_content";
  }


  public function getEpisode($start, $finish) {
    $this->addTag("radio_StationContentQuery_modifyGetEpisode");
    $this->addTag("parameter_StationContentQuery__{$start}__{$finish}");
    return $this;
  }


  public function getContentByProgram($program_nid) {
    $this->fieldCondition(
      "field_produced_for",
      "target_id",
      $program_nid,
      "="
    );

    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
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


  public function hasAudio() {
    $subquery = db_select('field_data_field_audio_files', 'f');
    $subquery->distinct();
    $subquery->addField('f', 'entity_id');
    $subquery->condition('f.deleted', '0', '=');
    $subquery->condition('f.field_audio_files_fid', 'NULL', '!=');

    $this->entityCondition('entity_id', $subquery, 'IN');
  }


  public function latestAudio($count) {
    $this->type('Episode');
    $this->setLimit($count);
    $this->hasAudio();
    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
  }


  public function olderThan($timestamp) {
    $this->fieldCondition('field_air_time', 'value', $timestamp, '<=');
    return $this;
  }


  public static function modifyGetEpisode(QueryAlterableInterface $query) {
    $start = $finish = time();
    $tags = $query->alterTags;

    foreach ($tags as $tag => $value) {
      if (Helpers::startsWith($tag, "parameter_StationContentQuery")) {
        $parts = explode("__", $tag);
        $start = $parts[1];
        $finish = $parts[2];
        break;
      }
    }

    NodeQuery::joinField($query, "field_air_time");
    NodeQuery::dateFieldEquals($query, "field_air_time", $start, $finish);
  }
}
