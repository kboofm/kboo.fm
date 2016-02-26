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
        $variables = [
          'foo' => "Hello Dolly!",
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
