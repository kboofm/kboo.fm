<?php

class NewsResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_news';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $component = new NewsComponent();
    $pager = $component->latest($page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
