<?php

class ProgramQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'program';
  }


  /**
   * Get streams matching the $string
   *
   * @return $this
   */
  public function getStreams() {
    $this->getProgramsByType('Channel/Stream');
    return $this;
  }


  /**
   * Get shows matching the $string
   *
   * @param $status
   * @param $streams
   * @return $this
   */
  public function getShows($status, $streams) {
    $this->getProgramsByType('Show');
    $this->hasAnyStream($streams);

    $this->fieldCondition(
      "field_program_status",
      "value",
      $status,
      "="
    );

    return $this;
  }


  protected function hasAnyStream($streams) {
    if (!is_array($streams)) {
      $streams = [$streams];
    }

    $streams = array_map(
      function ($stream) {
        return Helpers::getStreamNid($stream);
      },
      $streams
    );

    $this->fieldCondition(
      "field_streams",
      "target_id",
      $streams,
      "IN"
    );
  }


  public function hasGenre() {
    $this->fieldCondition("field_genres", "tid", "NULL", "!=");
    return $this;
  }


  public function hasTopic() {
    $this->fieldCondition("field_topic_tags", "tid", "NULL", "!=");
    return $this;
  }


  private function getProgramsByType($term_name) {
    $terms = taxonomy_get_term_by_name($term_name, 'program_types');
    $term = reset($terms);

    $this->fieldCondition('field_program_type', 'tid', $term->tid);
    return $this;
  }
}