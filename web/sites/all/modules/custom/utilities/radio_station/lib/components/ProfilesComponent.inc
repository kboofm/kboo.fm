<?php

class ProfilesComponent extends BaseComponent {

  public function getContributors() {
    $query = new PersonProfileQuery();
    $query->getContributors();
    $result = $query->execute();

    $processor = new ListProcessor();
    return $processor->process(
      $this->getNids($result)
    );
  }


  public function getShowHosts($contains = null, $status = null) {
    $query = new PersonProfileQuery();
    $query->getShowHosts($status);
    $query->searchTitle($contains);
    $result = $query->execute();

    $processor = new ListProcessor();
    $profiles = $processor->process(
      $this->getNids($result)
    );

    return $processor->groupAlphabetically($profiles);
  }
}
