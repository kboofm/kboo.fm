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


  public function group($data) {
    $alphabet = array_fill_keys(
      range('A', 'Z'),
      []
    );

    # This will hold all non-alphabetic titles
    $alphabet['#'] = [];

    foreach ($data as $item) {
      $first_letter = strtoupper($item['title'][0]);

      if (isset($alphabet[$first_letter])) {
        $alphabet[$first_letter][] = $item;
      } else {
        $alphabet['#'][] = $item;
      }
    }

    $alphabet = array_filter(
      $alphabet,
      function ($item) {
        return (count($item) > 0);
      }
    );

    return $alphabet;
  }
}
