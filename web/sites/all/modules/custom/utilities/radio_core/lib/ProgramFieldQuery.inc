<?php

class ProgramFieldQuery extends NodeFieldQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->bundle = 'program';
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

    $this->fieldCondition('field_program_type', 'tid', $term->tid)
      ->fieldCondition('title_field', 'value', $string, 'CONTAINS')
      ->range(0, 10);

    return $this;
  }
}