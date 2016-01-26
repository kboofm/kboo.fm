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


  public function getLivewireEvents() {
    return $this->getUpcomingEventsByTermName('Livewire music event');
  }


  public function getLivewireInRange($earliest, $latest) {
    $terms = taxonomy_get_term_by_name('Livewire music event', 'event_types');
    $term = reset($terms);

    if (isset($term->tid)) {
      $this->fieldCondition(
        'field_event_type',
        'tid',
        $term->tid
      );
    }

    $this->addTag('radio_EventQuery_eventDateInRange');
    NodeQuery::addParam('range', [$earliest, $latest]);

    $this->fieldOrderBy('field_event_date', 'value');
    return $this;
  }


  public function getLiveEvents() {
    return $this->getUpcomingEventsByTermName('Live broadcast');
  }


  public function getPreviousLiveEvents() {
    return $this->getPreviousEventsByTermName('Live broadcast');
  }


  public function getCommunityEvents() {
    return $this->getUpcomingEventsByTermName('Community event');
  }


  public function getLatestTakingItToTheStreets() {
    $this->getUpcomingEventsByTermName('Takin It To The Streets');
    return $this;
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


  private function getPreviousEventsByTermName($termName) {
    $terms = taxonomy_get_term_by_name($termName, 'event_types');
    $term = reset($terms);

    $event_begin = time(); // Now

    # where
    if (isset($term->tid)) {
      $this->fieldCondition('field_event_type', 'tid', $term->tid);
    }

    $this->fieldCondition('field_event_date', 'value', $event_begin, '<');

    # order by
    $this->fieldOrderBy('field_event_date', 'value', 'DESC');

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
