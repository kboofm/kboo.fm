<?php

/**
 * Register a File migration
 */
class FileRegistration extends BaseRegistration {

  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();

    $this->custom_args = [
      'group_name' => 'Core',
      'machine_name' => 'File',
      'class_name' => 'DrupalFile6Migration',
      'description' => t('Import Drupal 6 files'),
      'user_migration' => 'User',
      'default_uid' => 1,
      'source_dir' => 'http://www.kboo.fm',
      'destination_dir' => 'public://',
      'dependencies' => [
        'User',
      ],
    ];
  }
}
