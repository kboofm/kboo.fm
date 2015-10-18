<?php
require_once (dirname(__DIR__)) . '../radio_template_query/lib/utilities/Helpers.inc';


class RadioStationCallbacks {
  /**
   * Build callback routes array for hook_menu
   *
   * @return array
   */
  public static function buildRoutes() {
    $items = [];

    $items['station/episode/%/%'] = array(
      'title' => 'Get Episode',
      'page callback' => 'radio_station_get_episode',
      'page arguments' => array(2, 3),
      'access arguments' => array('access content'),
      'type' => MENU_CALLBACK,
    );


    $items['station/day/%/%'] = array(
      'title' => 'Get Day',
      'page callback' => 'radio_station_get_day',
      'page arguments' => array(2, 3),
      'access arguments' => array('access content'),
      'type' => MENU_CALLBACK,
    );

    $items['station/week/%/%'] = array(
      'title' => 'Get Week',
      'page callback' => 'radio_station_get_week',
      'page arguments' => array(2, 3),
      'access arguments' => array('access content'),
      'type' => MENU_CALLBACK,
    );

    return $items;
  }

  public static function getEpisode($direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    $method = ($direction == 'prev') ? 'getPrevious' : 'getNext';
    $query->$method($timestamp);
    $result = $query->execute();

    return RadioStationCallbacks::processResponse(
      $result,
      $direction,
      $timestamp
    );
  }


  public static function getDay($direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    if ($direction == 'prev') {
      $start = Helpers::dayBeforeBegin($timestamp);
    } else {
      $start = Helpers::dayAfterBegin($timestamp);
    }

    $end = Helpers::dayEnd($start);
    $query->getRange($start, $end);
    $result = $query->execute();

    return RadioStationCallbacks::processRangeResponse(
      $result,
      $start,
      $end
    );
  }


  public static function getWeek($direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    if ($direction == 'prev') {
      $start = Helpers::weekBeforeBegin($timestamp);
    } else {
      $start = Helpers::weekAfterBegin($timestamp);
    }

    $end = Helpers::weekEnd($start);
    $query->getRange($start, $end);
    $result = $query->execute();

    return RadioStationCallbacks::processRangeResponse(
      $result,
      $start,
      $end,
      true
    );
  }


  public static function processRangeResponse($result, $start, $end, $groupByDay) {
    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $data = $processor->processRange(
      $result['node'],
      $start,
      $end,
      $groupByDay
    );

    return $data;
  }

  public static function processResponse($result, $direction, $timestamp) {
    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $when = ($direction == 'prev') ? 'before' : 'after';
    $data = $processor->process(
      $result['node'],
      $timestamp,
      $when
    );

    return $data;
  }
}