<?php

class NewsQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_types = [
      'blog_post',
      'promo',
      'station_content',
    ];
  }


  public function getLatest() {
    $this->addTag('radio_NodeQuery_orderByPublicationDateOrCreated');
    return $this;
  }
}
