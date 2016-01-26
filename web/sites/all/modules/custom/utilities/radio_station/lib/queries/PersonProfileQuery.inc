<?php



class PersonProfileQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'person_profile';
  }


  /**
   * Get authors
   *
   * @return $this
   */
  public function getContributors() {
    $terms = taxonomy_get_term_by_name('Author', 'profile_types');
    $author_term = reset($terms);

    $terms = taxonomy_get_term_by_name('Staff', 'profile_types');
    $staff_term = reset($terms);

    $tids = [
      $author_term->tid,
      $staff_term->tid,
    ];

    $this->fieldCondition(
      'field_profile_type',
      'tid',
      $tids,
      'IN'
    );

    $this->sortByTitle();
    return $this;
  }


  /**
   * Get show hosts
   *
   * @param null $status
   * @return $this
   */
  public function getShowHosts($status = null) {
    if ($status == EShowHostStatus::Both) {
      $status = null;
    }

    $terms = taxonomy_get_term_by_name('Show Host', 'profile_types');
    $term = reset($terms);

    $this->fieldCondition('field_profile_type', 'tid', $term->tid);

    if (!is_null($status)) {
      $this->fieldCondition('field_show_host_status', 'value', $status);
    }

    $this->sortByTitle();
    return $this;
  }
}