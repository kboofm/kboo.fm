<?php

class ProgramsComponent extends BaseComponent {

  public function getCurrentShows() {
    $query = new ProgramQuery();

    $query->getShows(
      EProgramStatus::Current,
      EStreams::One
    );

    $query->sortByTitle();
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    return array_values(
      node_load_multiple($nids)
    );
  }


  public function getRetiredShows() {
    $query = new ProgramQuery();

    $query->getShows(
      EProgramStatus::Retired,
      EStreams::all()
    );

    $query->sortByTitle();
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    return array_values(
      node_load_multiple($nids)
    );
  }


  public function getWebOnlyShows() {
    $query = new ProgramQuery();

    $query->getShows(
      EProgramStatus::Current,
      EStreams::Two
    );

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

    $query->getShows(
      EProgramStatus::Current,
      EStreams::One
    );

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

    $query->getShows(
      EProgramStatus::Current,
      EStreams::One
    );

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
