<?php
class StationContentQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = "station_content";
  }


  public function getEpisode($start, $end) {
    $daterange = [
      $start,
      $end
    ];

    $this->type('Episode');
    $this->addTag("radio_StationContentQuery_modifyGetEpisode");
    NodeQuery::addParam('daterange', $daterange);
    return $this;
  }


  public function getEpisodeInRange($start, $end) {
    $daterange = [
      $start,
      $end
    ];

    $this->type('Episode');
    $this->addTag('radio_StationContentQuery_modifyGetEpisodeInRange');
    NodeQuery::addParam('daterange', $daterange);
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


  public function getPodcastByGenre($target) {
    $this->fieldCondition(
      "field_genres",
      "tid",
      $target,
      "="
    );

    $this->fieldCondition(
      "field_audio_files",
      "fid",
      "NULL",
      "!="
    );

    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
    return $this;
  }


  public function getPodcastByTopic($target) {
    $this->fieldCondition(
      "field_topic_tags",
      "tid",
      $target,
      "="
    );

    $this->fieldCondition(
      "field_audio_files",
      "fid",
      "NULL",
      "!="
    );

    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
    return $this;
  }


  public function getPodcastByProgram($target_nid) {
    $this->fieldCondition(
      "field_produced_for",
      "target_id",
      $target_nid,
      "="
    );

    $this->fieldCondition(
      "field_audio_files",
      "fid",
      "NULL",
      "!="
    );

    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
    return $this;
  }


  public function getPodcastByProfile($target_nid) {
    $this->fieldCondition(
      "field_hosted_by",
      "target_id",
      $target_nid,
      "="
    );

    $this->fieldCondition(
      "field_audio_files",
      "fid",
      "NULL",
      "!="
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


  public function getAudio() {
    $this->type('Episode');
    $this->hasAudio();
    $this->propertyOrderBy('sticky', 'DESC');
    $this->fieldOrderBy('field_air_time', 'value');
    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
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
    $now = time();
    $default = [$now, $now];
    list($start, $end) = NodeQuery::getParam('daterange', $default);

    NodeQuery::joinField($query, "field_air_time");
    NodeQuery::dateFieldEquals($query, "field_air_time", $start, $end);
  }


  public static function modifyGetEpisodeInRange(
    QueryAlterableInterface $query
  ) {

    $now = time();
    $default = [$now, $now];
    list($start, $end) = NodeQuery::getParam('daterange', $default);

    NodeQuery::joinField($query, 'field_air_time');
    NodeQuery::dateFieldInRange($query, 'field_air_time', $start, $end);
  }
}
