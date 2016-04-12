<?php

class ProgramsComponent extends BaseComponent {

  public function getShows($status, $streams) {
    $query = new ProgramQuery();

    $query->getShows(
      $status,
      $streams
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
      EStreams::all()
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
      EStreams::all()
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
