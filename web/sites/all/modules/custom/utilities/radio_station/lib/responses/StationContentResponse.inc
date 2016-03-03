<?php

class StationContentResponse extends Response {

  public function getAudio() {
    $this->template_name = 'radio_template_audio';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $component = new StationContentComponent();
    $pager = $component->getAudio($page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getAudioFeed() {
    $component = new StationContentComponent();
    $nids = $component->getAudioFeed();
    node_feed($nids);
  }
}
