<?php

class HomeResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_home';

    $component = new HomeComponent();
    $items = $component->latest();

    $data = [
      'items' => $items,
    ];

    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getFeed() {
    $component = new HomeComponent();
    $nids = $component->latestFeed();

    $channel = [
      'title' => "KBOO - Community Radio for Portland and beyond",
    ];
    node_feed($nids, $channel);
  }
}
