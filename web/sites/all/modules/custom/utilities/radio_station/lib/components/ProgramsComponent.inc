<?php

class ProgramsComponent extends BaseComponent {

  public function getShows() {
    $query = new ProgramQuery();
    $query->getShows();
    $query->sortByTitle();
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    return array_values(
      node_load_multiple($nids)
    );
  }
}
