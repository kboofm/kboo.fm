<?php

class BlogPostQuery extends NodeQuery {

  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'blog_post';
  }


  public function getLatestByShowHosts() {
    # where
    $this->hasLeadImage();
    $this->fieldCondition('field_is_show_host', 'value', 1);

    # order by
    $this->sortByPromotedSticky();
    $this->sortByPublished();

    return $this;
  }


  public function getLatest() {
    $this->addTag('radio_NodeQuery_orderByPublicationDateOrCreated');
    return $this;
  }
}
