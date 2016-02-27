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
    $block = [];

    switch($delta) {
      case 'sidebar-audio':
        $component = new StationContentComponent();
        $variables = [
          'items' => $component->latestAudio(),
        ];

        $block['content'] = theme(
          'radio_template_sidebar_audio',
          $variables
        );
        break;

      case 'sidebar-playlists':
        $component = new StationContentComponent();
        $variables = [
          'items' => $component->latestAudio(),
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
