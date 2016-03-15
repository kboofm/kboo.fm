<?php


/**
 * Migrates D7 book from D6 book.
 */
class BookFromBook extends NodeImageMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

    $this->addFieldMapping(
      'migrate_redirects',
      'path'
    );

    $this->addUploadMapping("field_files");

    parent::__construct($arguments);
  }
}
