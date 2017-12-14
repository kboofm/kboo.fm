<?php
class StationContentQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = "station_content";
  }


  public function getContent($start, $end) {
    $daterange = [
      $start,
      $end
    ];

    $this->addTag("radio_StationContentQuery_modifyGetContent");
    NodeQuery::addParam('daterange', $daterange);
    return $this;
  }


  public function getContentInRange($start, $end) {
    $daterange = [
      $start,
      $end
    ];

    $this->addTag('radio_StationContentQuery_modifyGetContentInRange');
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

    $this->fieldOrderBy("field_air_time", "value", "DESC");
    return $this;
  }


  public function getUpcomingByProgram($program_nid, $count = NULL) {
    $this->fieldCondition(
      "field_air_time",
      "value",
      time(),
      ">"
    );

    $this->fieldCondition(
      "field_produced_for",
      "target_id",
      $program_nid,
      "="
    );

    if ($count) {
      $this->setLimit($count);
    }

    $this->fieldOrderBy("field_air_time", "value", "ASC");
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


  public function getPodcastByProgram($target_nid, $count = NULL) {
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

    $this->fieldOrderBy('field_air_time', 'value', 'DESC');
    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");

    if ($count) {
      $this->setLimit($count);
    }
    
    return $this;
  }

  public function getContentByHost($hp_id) {
    $this->fieldCondition(
      "field_hosted_by",
      "target_id",
      $hp_id,
      "="
    );

    $this->fieldOrderBy("field_air_time", "value", "DESC");
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


  public function hasAudio() {
    $subquery = db_select('field_data_field_audio_files', 'f');
    $subquery->distinct();
    $subquery->addField('f', 'entity_id');
    $subquery->condition('f.deleted', '0', '=');
    $subquery->condition('f.field_audio_files_fid', 'NULL', '!=');

    $this->entityCondition('entity_id', $subquery, 'IN');
  }


  public function getAudio($count = null, $publiconly = FALSE) {
    $this->hasAudio();

    if ($count) {
      $this->setLimit($count);
    }

	if($publiconly)
	{
		$this->fieldCondition('field_episode_record', 'value', '2', '=');
	}
    $this->propertyOrderBy('sticky', 'DESC');
    $this->fieldOrderBy('field_air_time', 'value', 'DESC');
    $this->addTag("radio_NodeQuery_orderByPublicationDateOrCreated");
  }


  public function olderThan($timestamp) {
    $this->fieldCondition('field_air_time', 'value', $timestamp, '<=');
    return $this;
  }


  public static function modifyGetContent(QueryAlterableInterface $query) {
    $now = time();
    $default = [$now, $now];
    list($start, $end) = NodeQuery::getParam('daterange', $default);

    NodeQuery::joinField($query, "field_air_time");
    NodeQuery::dateFieldEquals($query, "field_air_time", $start, $end);
  }


  public static function modifyGetContentInRange(
    QueryAlterableInterface $query
  ) {

    $now = time();
    $default = [$now, $now];
    list($start, $end) = NodeQuery::getParam('daterange', $default);

    NodeQuery::joinField($query, 'field_air_time');
    NodeQuery::dateFieldInRange($query, 'field_air_time', $start, $end);
  }
}
