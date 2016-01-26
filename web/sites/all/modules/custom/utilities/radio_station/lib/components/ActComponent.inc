<?php

class ActComponent extends BaseComponent {

  public function getSelect2($startswith) {
    $query = new ActQuery();
    $query->get($startswith);
    $query->setLimit(10);
    $result = $query->execute();

    $processor = new ListProcessor();
    $list = $processor->processSelect2(
      $this->getNids($result)
    );

    return [
      'results' => $list,
      'more' => false
    ];
  }
}
