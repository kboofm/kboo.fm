<?php

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

    return $items;
  }

  public static function getEpisode($direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    if ($direction == 'prev') {
      $method = 'getPrevious';
    } else {
      $method = 'getNext';
    }

    $query->$method($timestamp);
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    if ($direction == 'prev') {
      $method = 'processBefore';
    } else {
      $method = 'processAfter';
    }

    $data = $processor->$method(
      $result['node'],
      $timestamp
    );

    if ($data) {
      $data = $data[0];
    }

    return $data;
  }
}