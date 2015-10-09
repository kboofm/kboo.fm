<?php

class Helpers {
  /**
   * @param $haystack
   * @param $needle
   * @return bool
   */
  public static function startsWith($haystack, $needle) {
    return $needle === "" || strrpos($haystack, $needle, -strlen($haystack)) !== FALSE;
  }


  /**
   * Check if string ends with substring
   *
   * @param $haystack
   * @param $needle
   * @return bool
   */
  public static function endsWith($haystack, $needle) {
    return substr($haystack, -strlen($needle)) === $needle;
  }
}
