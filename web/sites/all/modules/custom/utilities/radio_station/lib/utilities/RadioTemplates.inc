<?php

class RadioTemplates {
  private $templates;
  private $path;


  public function __construct() {
    $this->templates = [];
    $this->path = drupal_get_path('module', 'radio_station') . '/templates';
  }


  public function get() {
    $this->addTemplate('audio_player');
    $this->addTemplate('blog');
    $this->addTemplate('community_events');
    $this->addTemplate('episode_playlists');
    $this->addTemplate('listen');
    $this->addTemplate('news');
    $this->addTemplate('programs_content');
    $this->addTemplate('programs_playlists');
    $this->addTemplate('schedule');

    return $this->templates;
  }


  private function addTemplate($name, $variables = []) {
    // Ensure correct format, either hyphened name or underscored name
    $hyphened = str_replace('_', '-', $name);
    $underscored = str_replace('-', '_', $name);

    $template_name = "radio_template_{$underscored}";
    $this->templates[$template_name] = [
      'template' => $hyphened,
      'path' => $this->path,
      'variables' => $variables,
    ];
  }
}
