<?php

abstract class MigrationSettings {
  public static function database() {
    return array(
      'driver' => 'mysql',
      'database' => '',
      'username' => '',
      'password' => '',
      'host' => 'localhost',
      'port' => '',
      'prefix' => '',
    );
  }
}
