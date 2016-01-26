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


  public function getPodcastByProgram($program_nid) {
    $this->fieldCondition(
      "field_produced_for",
      "target_id",
      $program_nid,
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
