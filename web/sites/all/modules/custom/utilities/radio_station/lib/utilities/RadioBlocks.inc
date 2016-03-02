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
    $block = [];

    switch($delta) {
      case 'sidebar-audio':
        $component = new StationContentComponent();
        $episodes = $component->latestAudio($count);

        $variables = [
          'episodes' => $episodes,
        ];

        $block['content'] = theme(
          'radio_template_sidebar_audio',
          $variables
        );
        break;

      case 'sidebar-playlists':
        $component = new StationContentComponent();
        $playlists = $component->latestPlaylists($count);

        $variables = [
          'playlists' => $playlists,
        ];

        $block['content'] = theme(
          'radio_template_sidebar_playlists',
          $variables
        );
        break;
    }

    return $block;
  }
}
