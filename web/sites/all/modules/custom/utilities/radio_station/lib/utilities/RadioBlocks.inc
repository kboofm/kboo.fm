<?php

class RadioBlocks {

  public function get() {
    $blocks = [];

    $blocks['sidebar-audio'] = [
      'info' => t('Sidebar Audio'),
    ];

    $blocks['sidebar-playlists'] = [
      'info' => t('Sidebar Playlists'),
    ];

    return $blocks;
  }


  public function view($delta) {
    $count = 6;

    switch($delta) {
      case 'sidebar-audio':
        return $this->viewSidebarAudio($count);

      case 'sidebar-playlists':
        return $this->viewSidebarPlaylists($count);
    }
  }


  private function viewSidebarAudio($count) {
    $block = [];
    $component = new StationContentComponent();
    $episodes = $component->latestAudio($count);

    $variables = [
      'episodes' => $episodes,
    ];

    $block['content'] = theme(
      'radio_template_sidebar_audio',
      $variables
    );

    return $block;
  }


  private function viewSidebarPlaylists($count) {
    $block = [];
    $component = new StationContentComponent();
    $playlists = $component->latestPlaylists($count);

    $variables = [
      'playlists' => $playlists,
    ];

    $block['content'] = theme(
      'radio_template_sidebar_playlists',
      $variables
    );

    return $block;
  }
}
