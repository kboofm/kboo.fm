<?php

class OrganizationFieldQuery extends NodeFieldQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->bundle = 'organization';
  }


  /**
   * Get streams matching the $string
   *
   * @param $string
   * @return $this
   */
  public function getVenues($string) {
    $terms = taxonomy_get_term_by_name('Venue', 'organization_types');
    $term = reset($terms);

    $this->fieldCondition('field_organization_type', 'tid', $term->tid)
      ->fieldCondition('title_field', 'value', $string, 'CONTAINS')
      ->range(0, 10);

    return $this;
  }
}