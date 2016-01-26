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
    return $this->getProgramsByType('Channel/Stream');
  }


  /**
   * Get shows matching the $string
   *
   * @return $this
   */
  public function getShows() {
    return $this->getProgramsByType('Show');
  }


  private function getProgramsByType($term_name) {
    $terms = taxonomy_get_term_by_name($term_name, 'program_types');
    $term = reset($terms);

    $this->fieldCondition('field_program_type', 'tid', $term->tid);
    return $this;
  }
}