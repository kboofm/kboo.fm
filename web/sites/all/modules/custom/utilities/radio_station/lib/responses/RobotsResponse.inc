<?php

include_once('Response.inc');
class RobotsResponse extends Response {
  public function get() {
    $env = RadioConfig::environment();
    $data = $this->getDefaultContent();

    if ($env) {
      $path = drupal_get_path("module", "radio_station");
      $robots_file = "{$path}/robots/{$env}.txt";

      if (file_exists($robots_file)) {
        $data = file_get_contents($robots_file);
      }
    }

    $this->addTemplateData([$data]);
    $this->renderTxt();
  }


  private function getDefaultContent() {
    return <<<TEXT
User-agent: *
Disallow: /
TEXT;
  }
}
