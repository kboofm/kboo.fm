<?php

class NodeQuery extends EntityFieldQuery {
  private static $params;
  protected $content_type;
  protected $content_types;

  protected function initialize() {}

  /**
   * Constructor
   *
   */
  public function __construct() {
    $this->entityCondition('entity_type', 'node');
    $this->propertyCondition('status', 1);
    $this->initialize();
    $this->setBundle();
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


  public function setLimit($count) {
    if ($count) {
      $this->range(0, $count);
    }
  }


  public function isPromoted() {
    $this->propertyCondition('promote', 1, '=');
  }


  protected function hasLeadImage() {
    $this->fieldCondition('field_lead_image', 'fid', 'NULL', '!=');
  }


  public function sortByTitle() {
    $this->fieldOrderBy('title_field', 'value');
  }


  public function sortByPromotedSticky() {
    $this->propertyOrderBy('promote', 'DESC');
    $this->propertyOrderBy('sticky', 'DESC');
  }


  protected function sortByPublished() {
    $this->addTag('radio_NodeQuery_orderByPublicationDate');
  }


  protected function dateFieldIsAfter($fieldname, $timestamp) {
    $this->fieldCondition($fieldname, 'value', $timestamp, '>');
  }


  protected function dateFieldIsBefore($fieldname, $timestamp) {
    $this->fieldCondition($fieldname, 'value', $timestamp, '<');
  }


  protected static function addParam($name, $value) {
    NodeQuery::$params[$name] = $value;
  }


  protected static function getParam($name, $default = NULL) {
    $exists = array_key_exists($name, NodeQuery::$params);
    if ($exists) {
      return NodeQuery::$params[$name];
    }

    return $default;
  }


  public function amongNodes($nids) {
    if (!is_array($nids)) {
      $nids = [$nids];
    }

    $this->entityCondition('entity_id', $nids, 'IN');
  }


  public function excludeNodes($nids) {
    if (!is_array($nids)) {
      $nids = [$nids];
    }

    $this->entityCondition('entity_id', $nids, 'NOT IN');
  }


  public function search(
    $field,
    $value,
    $search_type = EStringSearchOptions::Contains
  ) {

    return $this->searchColumn($field, 'value', $value, $search_type);
  }


  public function searchTitle(
    $value,
    $search_type = EStringSearchOptions::Contains
  ) {

    return $this->search('title_field', $value, $search_type);
  }


  public function searchColumn(
    $field,
    $column,
    $value,
    $search_type = EStringSearchOptions::Contains,
    $delta_group = null
  ) {

    if (!$value) {
      return;
    }

    switch ($search_type) {
      case EStringSearchOptions::Contains:
        $this->fieldCondition(
          $field,
          $column,
          $value,
          'CONTAINS',
          $delta_group
        );
        break;

      case EStringSearchOptions::Equals:
        $this->fieldCondition(
          $field,
          $column,
          $value,
          '=',
          $delta_group
        );
        break;

      case EStringSearchOptions::StartsWith:
        $this->fieldCondition(
          $field,
          $column,
          "{$value}%",
          'LIKE',
          $delta_group
        );
        break;
    }
  }


  public function locationSearch($value, $search_type, $location_type) {
    return $this->searchColumn(
      'field_location',
      $location_type,
      $value,
      $search_type,
      'location'
    );
  }


  public static function joinField(
    QueryAlterableInterface $query,
    $fieldname
  ) {

    $query->join(
      "field_data_{$fieldname}",
      $fieldname,
      "node.nid = {$fieldname}.entity_id"
    );
  }


  public static function sortField(
    QueryAlterableInterface $query,
    $fieldname,
    $direction = 'ASC'
  ) {

    $query->orderBy("{$fieldname}.{$fieldname}_value", $direction);
  }


  public static function dateFieldEquals(
    QueryAlterableInterface $query,
    $fieldname,
    $start,
    $finish
  ) {

    $query->condition(db_and()
      ->condition("{$fieldname}.{$fieldname}_value", $start, "=")
      ->condition("{$fieldname}.{$fieldname}_value2", $finish, "=")
    );
  }


  public static function dateFieldInRange(
    QueryAlterableInterface $query,
    $fieldname,
    $start,
    $finish
  ) {

    /*
     * $start <= fieldname.value
     * fieldname.value2 <= $finish
     */
    $query->condition(db_and()
      ->condition("{$fieldname}.{$fieldname}_value", $start, ">=")
      ->condition("{$fieldname}.{$fieldname}_value2", $finish, "<=")
    );
  }


  public static function dateFieldOccurring(
    QueryAlterableInterface $query,
    $fieldname,
    $start,
    $finish
  ) {

    /*
     * fieldname.value <= $start
     * $finish <= fieldname.value2
     */
    $query->condition(db_and()
      ->condition("{$fieldname}.{$fieldname}_value", $start, "<=")
      ->condition("{$fieldname}.{$fieldname}_value2", $finish, ">=")
    );
  }


  public static function dateFieldAnyOccurring(
    QueryAlterableInterface $query,
    $fieldname,
    array $timestamps
  ) {

    /*
     * fieldname.value <= $start
     * $finish <= fieldname.value2
     */

    $db_or = db_or();

    foreach ($timestamps as $key => $timestamp) {
      if (!is_numeric($key)) {
        continue;
      }

      $start = $timestamp['value'];
      $finish = $timestamp['value2'];

      $db_or->condition(db_and()
        ->condition("{$fieldname}.{$fieldname}_value", $start, "<=")
        ->condition("{$fieldname}.{$fieldname}_value2", $finish, ">=")
      );
    }

    $query->condition($db_or);
  }


  public static function orderByPublicationDate(
    QueryAlterableInterface $query
  ) {

    $query->join(
      'publication_date',
      'publication_date',
      'node.nid = publication_date.nid'
    );

    $query->orderBy('publication_date.published_at', 'DESC');
  }


  public static function orderByPublicationDateOrCreated(
    QueryAlterableInterface $query
  ) {

    $query->leftJoin(
      'publication_date',
      'publication_date',
      'node.nid = publication_date.nid'
    );
    $query->orderBy('ifnull(publication_date.published_at, node.created)', 'DESC');
  }
}