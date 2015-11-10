<?php

/**
 * Register a UserPicture migration
 */
class UserPictureRegistration extends BaseRegistration {

  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();

    $this->custom_args = [
      'group_name' => 'Core',
      'description' => t('Migration of user pictures from Drupal 6'),
      'class_name' => 'DrupalPicture6Migration',
      'machine_name' => 'UserPicture',
      'default_uid' => 1,
      'source_dir' => 'http://backup.kboo.fm',
      'destination_dir' => 'public://',
    ];
  }

}
