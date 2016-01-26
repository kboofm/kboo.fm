<?php

class TakinItToTheStreetsQuery extends NodeQuery {
  protected function initialize() {
    $this->content_type = 'article';
    $title = "Takin' It to the Streets";

    # where
    $this->hasLeadImage();
    $this->propertyCondition('title', $title, '=');
    $this->setLimit(1);
  }
}
