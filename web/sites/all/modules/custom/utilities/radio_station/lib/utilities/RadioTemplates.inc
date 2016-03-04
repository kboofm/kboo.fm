<?php

class RadioTemplates {
  private $templates;
  private $path;


  public function __construct() {
    $this->templates = [];
    $this->path = drupal_get_path('module', 'radio_station') . '/templates';
  }


  public function get() {
    $this->addTemplate('audio');
    $this->addTemplate('audio_player');
    $this->addTemplate('blog');
    $this->addTemplate('community_events');
    $this->addTemplate('episode_playlists');
    $this->addTemplate('home');
    $this->addTemplate('listen_now');
    $this->addTemplate('news');
    $this->addTemplate('program');
    $this->addTemplate('program_content');
    $this->addTemplate('program_content_list');
    $this->addTemplate('program_genre');
    $this->addTemplate('program_playlists');
    $this->addTemplate('program_podcast');
    $this->addTemplate('program_topic');
    $this->addTemplate('profiles_podcast');
    $this->addTemplate('schedule');
    $this->addTemplate('sidebar_audio');
    $this->addTemplate('sidebar_playlists');
    $this->addTemplate('underwriters');

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
