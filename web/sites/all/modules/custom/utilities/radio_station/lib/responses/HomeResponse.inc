<?php

class HomeResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_home';

    $data = [
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
