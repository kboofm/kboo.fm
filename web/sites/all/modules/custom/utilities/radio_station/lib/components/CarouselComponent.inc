<?php

class CarouselComponent extends BaseComponent {
  public function promos($count) {
    $query = new PromoteLatestQuery();
    $query->getLatest();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new CarouselProcessor();
    return $processor->process(
      $this->getNodes($result)
    );
  }
}
