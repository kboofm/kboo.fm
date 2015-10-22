<?php

class CarouselComponent extends BaseComponent {
  public function promos($count) {
    $query = new PromoteLatestQuery($count);
    $query->getLatest();
    $result = $query->execute();

    $processor = new CarouselProcessor();
    return $processor->process(
      $this->getNodes($result)
    );
  }
}
