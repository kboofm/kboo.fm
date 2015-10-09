<?php

class PersonProfileQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'person_profile';
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

    # where
    $this->fieldCondition('field_profile_type', 'tid', $term->tid);
    $this->fieldCondition('title_field', 'value', $string, 'CONTAINS');

    # limit
    $this->range(0, 10);

    return $this;
  }
}