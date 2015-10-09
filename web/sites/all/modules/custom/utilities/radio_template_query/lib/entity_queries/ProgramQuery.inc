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
    $terms = taxonomy_get_term_by_name('Channel/Stream', 'program_types');
    $term = reset($terms);

    # where
    $this->fieldCondition('field_program_type', 'tid', $term->tid);
    $this->fieldCondition('title_field', 'value', $string, 'CONTAINS');

    # limit
    $this->range(0, 10);

    return $this;
  }
}