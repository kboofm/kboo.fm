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
   * @return $this
   */
  public function getShows() {
    $this->getProgramsByType('Show');
    return $this;
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