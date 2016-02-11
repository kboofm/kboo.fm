<?php

class EventQuery extends NodeQuery {
  /**
   * Initialize
   */
  public function initialize() {
    $this->content_type = 'event';
  }


  public function getLatest() {
    $this->addTag('radio_NodeQuery_orderByPublicationDateOrCreated');
    return $this;
  }


  public function getCommunityEvents() {
    return $this->getUpcomingEventsByTermName('Community events');
  }


  private function getUpcomingEventsByTermName($termName) {
    $terms = taxonomy_get_term_by_name($termName, 'event_types');
    $term = reset($terms);

    $event_begin = time(); // Now

    # where
    if (isset($term->tid)) {
      $this->fieldCondition('field_event_type', 'tid', $term->tid);
    }

    $this->fieldCondition('field_event_date', 'value', $event_begin, '>=');

    # order by
    $this->sortByPromotedSticky();
    $this->fieldOrderBy('field_event_date', 'value', 'ASC');

    return $this;
  }


  public static function eventDateInRange(QueryAlterableInterface $query) {
    $table = "field_data_field_event_date1";
    $range = NodeQuery::getParam("range");

    $db_or = db_or();
    $db_or->condition("{$table}.field_event_date_value", $range, "BETWEEN")
      ->condition("{$table}.field_event_date_value2", $range, "BETWEEN");

    $query->condition($db_or);
  }
}
