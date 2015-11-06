<?php

/**
 * Register a Role migration
 */
class RoleRegistration extends BaseRegistration {
  private $role_mappings;


  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();
    $this->defineRoleMappings();

    $this->custom_args = [
      'group_name' => 'Core',
      'description' => t('Migration of users from Drupal 6'),
      'class_name' => 'DrupalRole6Migration',
      'machine_name' => 'Role',
      'role_mappings' => $this->role_mappings,
    ];
  }


  /**
   * Define role mappings
   */
  private function defineRoleMappings() {

    // D6 => D7
    $this->role_mappings = [
      'anonymous user' =>
        'anonymous user',

      'authenticated user' =>
        'authenticated user',
    ];
  }
}
