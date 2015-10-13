<?php

class OrganizationQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'organization';
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

    # where
    $this->fieldCondition('field_organization_type', 'tid', $term->tid);
    $this->fieldCondition('title_field', 'value', $string, 'CONTAINS');

    # limit
    $this->range(0, 10);

    return $this;
  }
}