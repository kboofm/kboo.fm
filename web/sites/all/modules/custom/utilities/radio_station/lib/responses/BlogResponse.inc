<?php

include_once('Response.inc');
class BlogResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_blog';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $component = new BlogComponent();
    $pager = $component->latest($page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
