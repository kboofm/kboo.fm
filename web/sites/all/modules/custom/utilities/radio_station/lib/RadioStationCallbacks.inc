<?php
require_once (dirname(__DIR__)) . '/../radio_template_query/lib/utilities/Helpers.inc';


class RadioStationCallbacks {

  /**
   * Build callback routes array for hook_menu
   *
   * @return array
   */
  public static function buildRoutes() {
    $items = [];

    $items['station/episode/%/%/%'] = [
      'title' => 'Get Episode',
      'page callback' => 'radio_station_get_episode',
      'page arguments' => [2, 3, 4],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];


    $items['station/day/%/%/%'] = [
      'title' => 'Get Day',
      'page callback' => 'radio_station_get_day',
      'page arguments' => [2, 3, 4],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $items['station/week/%/%/%'] = [
      'title' => 'Get Week',
      'page callback' => 'radio_station_get_week',
      'page arguments' => [2, 3, 4],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $items['station/schedule/%'] = [
      'title' => 'Station Schedule',
      'page callback' => 'radio_station_get_schedule',
      'page arguments' => [2],
      'access arguments' => ['administer nodes'],
      'type' => MENU_CALLBACK,
    ];

    $items['station/playlist'] = [
      'title' => 'Station Playlist',
      'page callback' => 'radio_station_get_playlist',
      'access arguments' => ['administer nodes'],
      'type' => MENU_CALLBACK,
    ];

    return $items;
  }

  public static function getEpisode($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $query->getAt($stream, $timestamp);
        break;
      case 'prev':
        $query->getPrevious($stream, $timestamp);
        break;
      case 'next':
        $query->getNext($stream, $timestamp);
        break;
      default:
        return NULL;
    }
    $result = $query->execute();

    return RadioStationCallbacks::processResponse(
      $result,
      $direction,
      $timestamp
    );
  }


  public static function getDay($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $start = Helpers::dayBegin($timestamp);
        break;
      case 'prev':
      $start = Helpers::dayBeforeBegin($timestamp);
        break;
      case 'next':
      $start = Helpers::dayAfterBegin($timestamp);
        break;
      default:
        return NULL;
    }

    $end = Helpers::dayEnd($start);
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    return RadioStationCallbacks::processRangeResponse(
      $result,
      $start,
      $end
    );
  }


  public static function getWeek($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $start = Helpers::weekBegin($timestamp);
        break;
      case 'prev':
      $start = Helpers::weekBeforeBegin($timestamp);
        break;
      case 'next':
      $start = Helpers::weekAfterBegin($timestamp);
        break;
      default:
        return NULL;
    }

    $end = Helpers::weekEnd($start);
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    return RadioStationCallbacks::processRangeResponse(
      $result,
      $start,
      $end,
      true
    );
  }


  public static function getSchedule($stream) {
    return theme(
      'radio_station_schedule_template',
      ['stream' => $stream]
    );
  }


  public static function getPlaylist() {
    return theme(
      'radio_station_playlist_template',
      []
    );
  }


  public static function getTemplates() {
    return [
      'radio_station_schedule_template' => [
        'template' => 'schedule',
        'path' => drupal_get_path('module', 'radio_station') . '/templates',
        'variables' => [
          'results' => NULL,
        ],
      ],

      'radio_station_playlist_template' => [
        'template' => 'playlist',
        'path' => drupal_get_path('module', 'radio_station') . '/templates',
        'variables' => [
          'results' => NULL,
        ],
      ],
    ];
  }


  private static function processRangeResponse($result, $start, $end, $groupByDay = false) {
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

  private static function processResponse($result, $direction, $timestamp) {
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