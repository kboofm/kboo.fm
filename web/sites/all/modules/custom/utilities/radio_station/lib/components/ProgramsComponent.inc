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


  public function getGenres() {
    $query = new ProgramQuery();
    $query->getShows();
    $query->hasGenre();
    $query->sortByTitle();
    $result = $query->execute();

    $processor = new ProgramProcessor();
    $items = $processor->processGenres(
      $this->getNids($result)
    );

    return $processor->groupByKey($items, "genres");
  }


  public function getTopics() {
    $query = new ProgramQuery();
    $query->getShows();
    $query->hasTopic();
    $query->sortByTitle();
    $result = $query->execute();

    $processor = new ProgramProcessor();
    $items = $processor->processTopics(
      $this->getNids($result)
    );

    return $processor->groupByKey($items, "topics");
  }
}
