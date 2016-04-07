<?php

class RobotsResponse extends Response {
  public function get() {
    $data = <<<TEXT
User-agent: *
Disallow: /
TEXT;

    $path = drupal_get_path("module", "radio_station");
    $env_file = "{$path}/.env";

    if (file_exists($env_file)) {
      $env = trim(
        file_get_contents($env_file)
      );
      $robots_file = "{$path}/robots/{$env}.txt";

      if (file_exists($robots_file)) {
        $data = file_get_contents($robots_file);
      }
    }

    $this->addTemplateData([$data]);
    $this->renderTxt();
  }
}
