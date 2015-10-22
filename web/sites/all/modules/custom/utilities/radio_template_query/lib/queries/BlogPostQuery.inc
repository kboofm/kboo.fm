<?php

class BlogPostQuery extends NodeQuery {
  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'blog_post';
  }

  public function getLatest() {
    # where
    $this->hasLeadImage();
    $this->fieldCondition('field_is_show_host', 'value', 1);

    # order by
    $this->sortByPromotedSticky();
    $this->sortByPublished();

    return $this;
  }
}
