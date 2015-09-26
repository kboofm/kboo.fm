<?php

class PersonProfileFieldQuery extends NodeFieldQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->bundle = 'person_profile';
  }


  /**
   * Get show hosts matching the $string
   *
   * @param $string
   * @return $this
   */
  public function getShowHosts($string) {
    $terms = taxonomy_get_term_by_name('Show Host', 'profile_types');
    $term = reset($terms);

    $this->fieldCondition('field_profile_type', 'tid', $term->tid)
      ->fieldCondition('title_field', 'value', $string, 'CONTAINS')
      ->range(0, 10);

    return $this;
  }
}