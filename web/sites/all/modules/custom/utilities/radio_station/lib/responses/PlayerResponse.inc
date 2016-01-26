<?php

class PlayerResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_listen_now';
    return $this->renderHtml();
  }
}
