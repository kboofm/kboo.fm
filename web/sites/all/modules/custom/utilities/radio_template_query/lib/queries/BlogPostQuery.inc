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

    # order by
    $this->sortByPromotedSticky();
    $this->sortByPublished();

    return $this;
  }
}
