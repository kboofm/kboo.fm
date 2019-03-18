<?php

class HomeResponse extends Response {
  public function get($lang) {
    $this->template_name = 'radio_template_home';

    $component = new HomeComponent();
    $items = $component->latest($lang);

    $data = [
      'items' => $items,
    ];

    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getFeed($lang) {
    $component = new HomeComponent();
    $nids = $component->latestFeed($lang);

    $channel = [
      'title' => "KBOO - Community Radio for Portland and beyond",
    ];
    node_feed($nids, $channel);
  }
}
