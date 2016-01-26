<?php

class PromoteLatestQuery extends NodeQuery {
  public function getLatest() {
    # where
    $this->hasLeadOrTeaserImage();
    $this->fieldCondition('field_promote_to_wwoz_latest', 'value', 1);

    # order by
    $this->propertyOrderBy('sticky', 'DESC');
    $this->sortByPublished();

    return $this;
  }
}
