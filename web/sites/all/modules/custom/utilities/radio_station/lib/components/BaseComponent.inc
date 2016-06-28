<?php
require_once dirname(__DIR__) . '/utilities/Helpers.inc';


class BaseComponent {

  protected function getNodes($result) {
    if (isset($result['node'])) {
      return $result['node'];
    }

    return [];
  }


  protected function getNids($result) {
    if (isset($result['node'])) {
      return array_keys($result['node']);
    }

    return [];
  }
}
