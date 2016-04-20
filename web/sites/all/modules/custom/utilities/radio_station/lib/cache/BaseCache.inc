<?php

class BaseCache {
  public $table;
  public $keyPrefix;

  public function __construct() {
    $this->table = "cache_radio_station";
  }

  public function forceClear($postfix = "") {
    cache_clear_all(
      "{$this->keyPrefix}{$postfix}",
      $this->table,
      TRUE
    );
  }
}
