<?php

/**
 * Register a User migration
 */
class UserRegistration extends BaseRegistration {

  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();

    $this->custom_args = [
      'group_name' => 'Core',
      'description' => t('Migration of users from Drupal 6'),
      'class_name' => 'UserMigration',
      'machine_name' => 'User',
      'picture_migration' => 'UserPicture',
      'role_migration' => 'Role',
      'dependencies' => [
        'UserPicture',
        'Role',
      ],
    ];
  }
}
