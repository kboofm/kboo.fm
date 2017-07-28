<?php

abstract class MigrationSettings {
  public static function database() {
    return array(
      'driver' => 'mysql',
      'database' => 'kboo_backup',
      'username' => 'kboo',
      'password' => 'ArtHwaLedETHoS',
      'host' => 'localhost',
      'port' => '',
      'prefix' => '',
    );
  }
}
