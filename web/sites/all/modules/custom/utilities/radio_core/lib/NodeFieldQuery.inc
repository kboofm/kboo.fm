<?php

abstract class NodeFieldQuery extends EntityFieldQuery {
  protected $bundle;

  abstract protected function initialize();

  /**
   * Constructor
   */
  public function __construct() {
    $this->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1);

    $this->initialize();

    $this->entityCondition('bundle', $this->bundle);
  }
}