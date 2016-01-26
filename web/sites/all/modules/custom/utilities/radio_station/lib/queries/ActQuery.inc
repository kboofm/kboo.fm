<?php

class ActQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'act';
  }


  /**
   * Get acts matching the $string
   *
   * @param $startswith
   * @return $this
   */
  public function get($startswith) {
    $this->searchTitle($startswith, EStringSearchOptions::StartsWith);
    $this->sortByTitle();
    return $this;
  }
}
