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

  public static function dayBeforeBegin($timestamp) {
    return strtotime("yesterday midnight", $timestamp);
  }

  public static function dayBegin($timestamp) {
    return strtotime("midnight", $timestamp);
  }

  public static function dayEnd($timestamp) {
    return strtotime("tomorrow", $timestamp);
  }

  public static function dayAfterBegin($timestamp) {
    return Helpers::dayEnd($timestamp);
  }

  public static function todayBegin() {
    return strtotime("today midnight");
  }

  public static function weekBeforeBegin($timestamp) {
    return strtotime("-1 week last Sunday midnight", $timestamp);
  }

  public static function weekBegin($timestamp) {
    return strtotime("last Sunday midnight", $timestamp);
  }

  public static function weekEnd($timestamp) {
    return strtotime("next Sunday midnight", $timestamp);
  }

  public static function weekAfterBegin($timestamp) {
    return Helpers::weekEnd($timestamp);
  }

  public static function printif($array, $key) {
    if (isset($array[$key])) {
      print $array[$key];
    }
  }
}
