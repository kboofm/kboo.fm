<?php
$path = libraries_get_path('Carbon');
require_once "{$path}/Carbon.php";


use Carbon\Carbon;


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


  public static function timezone() {
    return variable_get('date_default_timezone', 'America/Chicago');
  }


  public static function toCarbonTimestamp($format, $value = NULL) {
    if (!$value) {
      $value = time();
    }

    $cdt = Carbon::createFromFormat(
      $format,
      $value,
      Helpers::timezone()
    );

    return $cdt->getTimestamp();
  }


  public static function toCarbonString($format, $value = NULL) {
    if (!$value) {
      $value = time();
    }

    $is_numeric = is_numeric($value);
    $is_object = is_object($value);

    if ($is_numeric || !$is_object) {
      $value = Helpers::carbonize($value);
    }

    return $value->format($format);
  }


  public static function carbonize($value = null) {
    if (!$value) {
      $value = time();
    }

    return Carbon::createFromTimestamp(
      $value,
      Helpers::timezone()
    );
  }


  public static function dayBeforeBegin($timestamp) {
    return Helpers::carbonize($timestamp)
      ->subDay()
      ->startOfDay()
      ->getTimestamp();
  }


  public static function dayBegin($timestamp) {
    return Helpers::carbonize($timestamp)
      ->startOfDay()
      ->getTimestamp();
  }


  public static function dayEnd($timestamp) {
    return Helpers::carbonize($timestamp)
      ->addDay()
      ->startOfDay()
      ->getTimestamp();
  }


  public static function dayAfterBegin($timestamp) {
    return Helpers::dayEnd($timestamp);
  }


  public static function todayBegin() {
    return Helpers::carbonize()
      ->startOfDay()
      ->getTimestamp();
  }


  public static function weekBeforeBegin($timestamp) {
    return Helpers::carbonize($timestamp)
      ->subWeek()
      ->modify('last Sunday')
      ->startOfDay()
      ->getTimestamp();
  }


  public static function weekBegin($timestamp) {
    return Helpers::carbonize($timestamp)
      ->modify('last Sunday')
      ->startOfDay()
      ->getTimestamp();
  }


  public static function weekEnd($timestamp) {
    return Helpers::carbonize($timestamp)
      ->modify('next Sunday')
      ->startOfDay()
      ->getTimestamp();
  }


  public static function weekAfterBegin($timestamp) {
    return Helpers::weekEnd($timestamp);
  }


  public static function printif($array, $key) {
    if (isset($array[$key])) {
      print $array[$key];
    }
  }


  public static function streamName($stream) {
    $match = in_array(
      strtolower($stream),
      ['stream1', 'stream 1']
    );

    if ($match || $stream == 1) {
      return EStreams::One;
    }

    return EStreams::Two;
  }


  public static function getQueryString() {
    $query = $_SERVER['QUERY_STRING'];
    $query = urldecode($query);
    return $query;
  }


  public static function getQueryParameters() {
    $query = Helpers::getQueryString();
    parse_str($query, $params);
    return $params;
  }


  public static function hasProtocol($url) {
    $http = Helpers::startsWith($url, "http://");
    $https = Helpers::startsWith($url, "https://");
    return ($http || $https);
  }


  public static function getProtocol() {
    $pos = stripos(
      $_SERVER['SERVER_PROTOCOL'],
      'https'
    );

    return ($pos === true) ? "https://" : "http://";
  }
}
