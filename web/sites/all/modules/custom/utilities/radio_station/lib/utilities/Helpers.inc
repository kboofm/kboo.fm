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
    return variable_get('date_default_timezone', 'America/Los_Angeles');
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
    $date = Helpers::carbonize($timestamp);

    if ($date->dayOfWeek != Carbon::SUNDAY) {
      $date->subWeek();
    }

    return $date->modify("last Sunday")
      ->startOfDay()
      ->getTimestamp();
  }


  public static function weekBegin($timestamp) {
    $date = Helpers::carbonize($timestamp);

    if ($date->dayOfWeek != Carbon::SUNDAY) {
      $date->modify('last Sunday');
    }

    return $date->startOfDay()
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


  public static function dayOfWeek($timestamp) {
    $day_of_week = Helpers::toCarbonString(
      'l',
      $timestamp
    );

    return strtolower($day_of_week);
  }


  public static function printif($array, $key) {
    if (isset($array[$key])) {
      print $array[$key];
    }
  }


  public static function getStreamNid($stream) {
    // If $stream is a number, then assume it is the stream nid
    if (is_numeric($stream)) {
      return (int)$stream;
    }

    if (!in_array($stream, EStreams::all())) {
      return NULL;
    }

    return variable_get("radio_station_stream_{$stream}_nid");
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


  public static function htmlToText($html) {
    // preg_replace is used to strip out any embedded media
    // Example:
    //   <p>[[{"fid":"20311","view_mode":"lead_image","type":"media",
    //   "attributes":{"height":"225","width":"300",
    //   "class":"media-element file-lead-image"}}]]</p>

    $html = preg_replace('/\[\[{.*}\]\]/', '', $html);
    $html = decode_entities($html);
    return drupal_html_to_text($html, []);
  }


  public static function getPublicFilesPath() {
    // http://drupal.stackexchange.com/a/56488
    $wrapper = file_stream_wrapper_get_instance_by_uri('public://');
    return $wrapper->realpath();
  }


  public static function watchEMWException($function, $trace) {
    watchdog(
      'radio_station',
      'EntityMetadataWrapper exception in %function() @trace',
      [
        '%function' => $function,
        '@trace' => $trace,
      ],
      WATCHDOG_ERROR
    );
  }
}
