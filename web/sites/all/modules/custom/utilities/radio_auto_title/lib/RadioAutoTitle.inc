<?php

class RadioAutoTitle {
  /**
   * Return the concatenated first and last name
   *
   * @param $node
   * @return string
   *
   */
  public static function getFullName($node) {
    $name = $node->field_name['und'][0];
    $first = isset($name['given']) ? $name['given'] : '';
    $last = isset($name['family']) ? $name['family'] : '';
    $separator = (!empty($first) && !empty($last)) ? ' ' : '';
    return $first . $separator . $last;
  }
}
