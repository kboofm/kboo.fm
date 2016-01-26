<?php

class PlayerResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_listen';
    return $this->renderHtml();
  }
}
