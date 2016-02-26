<?php

class RadioBlocks {

  public function get() {
    $blocks = [];

    $blocks['sidebar-audio'] = [
      'info' => t('Sidebar Audio'),
    ];

    return $blocks;
  }


  public function view($delta) {
    $block = [];

    switch($delta) {
      case 'sidebar-audio' :
        $component = new StationContentComponent();
        $variables = [
          'items' => $component->latestAudio(),
        ];

        $block['content'] = theme(
          'radio_template_sidebar_audio',
          $variables
        );
        break;
    }
    return $block;
  }
}
