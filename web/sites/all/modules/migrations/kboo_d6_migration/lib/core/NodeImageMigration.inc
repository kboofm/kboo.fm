<?php

class NodeImageMigration extends NodeMigration {
  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addImageMapping(
      'field_lead_image',
      'lead_image'
    );

    $this->addImageMapping(
      'field_more_images',
      'field_node_image'
    );

    parent::__construct($arguments);
  }


  /**
   * Prepare the source row
   *
   * @param $row
   * @return bool
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $row->lead_image = array_shift($row->field_node_image);
    return TRUE;
  }
}