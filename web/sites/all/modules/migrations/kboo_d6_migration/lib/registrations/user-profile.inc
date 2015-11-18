<?php

/**
 * Register a User migration
 */
class UserProfileRegistration extends BaseRegistration {

  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();

    $this->custom_args = [
      'group_name' => 'Profiles',
      'description' => t('Migration of user profiles from Drupal 6'),
      'class_name' => 'UserProfileMigration',
      'machine_name' => 'UserProfile',
      'dependencies' => [
        'User',
      ],
    ];
  }
}
