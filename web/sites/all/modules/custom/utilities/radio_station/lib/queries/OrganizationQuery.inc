<?php

class OrganizationQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'organization';
  }


  public function getVenues() {
    $terms = taxonomy_get_term_by_name('Venue', 'organization_types');
    $term = reset($terms);

    $this->fieldCondition('field_organization_type', 'tid', $term->tid);
    $this->sortByTitle();
    return $this;
  }
}