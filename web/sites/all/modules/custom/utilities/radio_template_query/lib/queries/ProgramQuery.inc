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
   * @param $string
   * @return $this
   */
  public function getStreams($string) {
    return $this->getProgramsByType('Channel/Stream', $string);
  }


  /**
   * Get shows matching the $string
   *
   * @param $string
   * @return $this
   */
  public function getShows($string) {
    return $this->getProgramsByType('Show', $string);
  }


  private function getProgramsByType($term_name, $title) {
    $terms = taxonomy_get_term_by_name($term_name, 'program_types');
    $term = reset($terms);

    $tid = NULL;
    if (isset($term->tid)) {
      $tid = $term->tid;
    }

    # where
    $this->fieldCondition('field_program_type', 'tid', $tid);
    $this->fieldCondition('title_field', 'value', $title, 'CONTAINS');

    # limit
    $this->range(0, 10);

    return $this;
  }
}