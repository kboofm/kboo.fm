<?php
class RadioConfigMissingException extends Exception {}


class RadioConfig {
  private static $config = null;


  private static function load() {
    if (self::$config) {
      return;
    }

    $path = drupal_get_path("module", "radio_station");
    $env_file = "{$path}/lib/configs/.env";

    if (!file_exists($env_file)) {
      throw new RadioConfigMissingException(
        "Radio station configuration file is missing"
      );
    }

    $env = trim(
      file_get_contents($env_file)
    );

    $config_file = "{$path}/lib/configs/{$env}.php";
    self::$config = include($config_file);
  }


  public static function all() {
    self::load();
    return self::$config;
  }


  public static function get($varname, $default = NULL) {
    self::load();

    if (!isset(self::$config[$varname])) {
      return $default;
    }

    return self::$config[$varname];
  }


  public static function has($varname) {
    self::load();
    return isset(self::$config[$varname]);
  }


  public static function environment() {
    return self::get("environment");
  }
}
