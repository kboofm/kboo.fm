<?php

class OrganizationQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'organization';
  }


  public function getVenues() {
    $this->type("Venue");
    $this->sortByTitle();
    return $this;
  }


  public function getSponsors() {
    $this->type("Sponsor");
    $this->sortByTitle();
    return $this;
  }


  private function type($term_name) {
    $terms = taxonomy_get_term_by_name($term_name, 'organization_types');
    $term = reset($terms);

    $tid = NULL;
    if (isset($term->tid)) {
      $tid = $term->tid;
    }

    $this->fieldCondition('field_organization_type', 'tid', $tid);
    return $this;
  }
}