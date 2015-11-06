<?php

/**
 * Abstract base class for registering migrations
 */
abstract class BaseRegistration {
  protected $common_args;
  protected $custom_args;


  /**
   * Constructor
   */
  public function __construct() {
    $this->defineCommonArguments();
  }


  /**
   * Define common arguments used by all registrations
   */
  protected function defineCommonArguments() {
    $this->common_args = [
      'source_connection' => 'legacy',
      'source_database' => MigrationSettings::database(),
      'source_version' => 6,
    ];
  }


  /**
   * Perform a migration registration
   */
  public function execute() {
    $args = array_merge(
      $this->common_args,
      $this->custom_args
    );

    Migration::registerMigration(
      $args['class_name'],
      $args['machine_name'],
      $args
    );
  }


  /**
   *
   * Instantiate object and execute registration
   *
   */
  public static function register() {
    $class = get_called_class();
    $object = new $class();
    $object->execute();
  }
}
