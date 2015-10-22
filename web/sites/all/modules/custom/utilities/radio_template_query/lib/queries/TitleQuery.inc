<?php

class TitleQuery extends NodeQuery {
  public function getLatest($title, $like = false) {
    $operator = '=';

    if ($like) {
      $title = "%{$title}%";
      $operator = 'like';
    }

    # where
    $this->hasLeadImage();
    $this->propertyCondition('title', $title, $operator);

    # order by
    $this->sortByPublished();

    return $this;
  }
}
