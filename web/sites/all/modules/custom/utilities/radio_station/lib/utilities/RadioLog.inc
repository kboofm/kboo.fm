<?php

class RadioLog {
  private $file;
  public $data;

  public function __construct($file) {
    $public_files = Helpers::getPublicFilesPath();
    $path = "{$public_files}/logs";

    if (!file_exists($path)) {
      mkdir($path, 0775);
    }

    $this->file = "{$path}/{$file}";
    $this->load();
  }


  private function load() {
    $json = file_get_contents($this->file);

    if ($json === false) {
      $this->data = [];
    } else {
      $this->data = json_decode($json, true);
    }
  }


  public function save() {
    $json = json_encode($this->data);
    file_put_contents($this->file, $json);
  }


  public function has($key) {
    return isset($this->data[$key]);
  }


  public function addTimestamped($content) {
    $now = time();
    $this->data[$now] = $content;
  }


  public function purgeTimestamped($timestamp) {
    $this->data = array_filter(
      $this->data,
      function ($key) use ($timestamp) {
        return ($key > $timestamp);
      },
      ARRAY_FILTER_USE_KEY
    );
  }
}
