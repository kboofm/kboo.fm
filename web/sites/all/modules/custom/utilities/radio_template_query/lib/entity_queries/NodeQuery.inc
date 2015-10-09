<?php

class NodeQuery extends EntityFieldQuery {
  protected $content_type;
  protected $content_types;

  protected function initialize() {}

  /**
   * Constructor
   *
   * @param null $count
   */
  public function __construct($count = NULL) {
    $this->entityCondition('entity_type', 'node');
    $this->propertyCondition('status', 1);

    $this->initialize();

    $this->setBundle();
    $this->setLimit($count);
  }


  private function setBundle() {
    $types = [];

    if ($this->content_type) {
      $types = [$this->content_type];
    }

    if ($this->content_types) {
      $types = array_merge(
        $types,
        $this->content_types
      );
    }

    if (!empty($types)) {
      $this->entityCondition('bundle', $types, 'IN');
    }
  }

  protected function setLimit($count) {
    if ($count) {
      $this->range(0, $count);
    }
  }

  protected function hasLeadImage() {
    $this->fieldCondition('field_lead_image', 'fid', 'NULL', '!=');
  }

  protected function sortByPromotedSticky() {
    # order by
    $this->propertyOrderBy('promote', 'DESC');
    $this->propertyOrderBy('sticky', 'DESC');
  }


  protected function sortByPublished() {
    # alter tag
    $this->addTag('radio_NodeQuery_orderByPublicationDate');
  }


  public static function orderByPublicationDate(QueryAlterableInterface $query) {
    $query->join(
      'publication_date',
      'publication_date',
      'node.nid = publication_date.nid'
    );

    $query->orderBy('publication_date.published_at', 'DESC');
  }
}
