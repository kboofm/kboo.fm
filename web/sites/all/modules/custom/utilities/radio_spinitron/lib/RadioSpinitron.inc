<?php
require_once (dirname(__DIR__)) . '/../radio_template_query/lib/utilities/Helpers.inc';


class RadioSpinitron {

  /**
   * Build callback routes array for hook_menu
   *
   * @return array
   */
  public static function buildRoutes() {
    $items = [];

    $items['spinitron/playlists/current'] = [
      'title' => 'Spinitron Playlist - Current',
      'page callback' => 'radio_spinitron_get_current_playlist',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $items['spinitron/playlists/day/%'] = [
      'title' => 'Spinitron Playlist - Day',
      'page callback' => 'radio_spinitron_get_playlist_day',
      'page arguments' => [3],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $items['spinitron/playlists/program/%'] = [
      'title' => 'Spinitron Playlist - Program',
      'page callback' => 'radio_spinitron_get_program_recent_playlists',
      'page arguments' => [3],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $items['spinitron/playlists/program/%/%'] = [
      'title' => 'Spinitron Playlist - Program (day)',
      'page callback' => 'radio_spinitron_get_program_playlist_day',
      'page arguments' => [3, 4],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    return $items;
  }


  /**
   * Get current playlist
   *
   * @return array|bool
   */
  public static function getCurrentPlaylist() {
    $spin = Spinitron::instance();
    return $spin->getCurrentPlaylist();
  }


  public static function getPlaylistDay($timestamp) {
    $date = date('Y-m-d', $timestamp);
    $spin = Spinitron::instance();
    $response = $spin->getPlaylistsByDate($date);
    return $response;
  }


  public static function getEpisodePlaylist($node) {
    $wrapped_node = entity_metadata_wrapper('node', $node);
    $field_air_time = $wrapped_node->field_air_time->value();

    $spin = Spinitron::instance();
    $date = date('Y-m-d', $field_air_time['value']);
    $response = $spin->getPlaylistsByDate($date);

    $response = array_filter(
      $response,
      function ($item) use ($field_air_time) {
        $start = $field_air_time['value'];
        $end = $field_air_time['value2'];

        $onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = strtotime($onair);

        $offair = "{$item['PlaylistDate']} {$item['OffairTime']}";
        $offair = strtotime($offair);

        if ($offair < $onair) {
          // If offair is the next day, then playlist date will be one day off
          $offair = strtotime("+1 day", $offair);
        }

        return ($start >= $onair && $end <= $offair);
      }
    );

    return $response;
  }


  /**
   * Get recent playlists for a program
   *
   * @param $program_nid
   * @return array|bool|null
   */
  public static function getProgramRecentPlaylists($program_nid) {
    $wrapped_node = entity_metadata_wrapper('node', $program_nid);

    if (!$wrapped_node) {
      return NULL;
    }

    $showId = $wrapped_node->field_spinitron_showid->value();

    if (!$showId) {
      return NULL;
    }

    $spin = Spinitron::instance();
    return $spin->getPlaylistsByShow($showId);
  }


  /**
   * Get playlist for a program at a given time
   *
   * @param $program_nid
   * @param $timestamp
   * @return null|string
   */
  public static function getProgramPlaylistDay($program_nid, $timestamp) {
    $wrapped_node = entity_metadata_wrapper('node', $program_nid);

    if (!$wrapped_node) {
      return NULL;
    }

    $showId = $wrapped_node->field_spinitron_showid->value();

    if (!$showId) {
      return NULL;
    }

    $spin = Spinitron::instance();
    $date = date('Y-m-d', $timestamp);
    $response = $spin->getPlaylistsByDate($date);

    $response = array_filter(
      $response,
      function ($item) use ($showId, $timestamp) {
        $onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = strtotime($onair);
        $dayBegin = Helpers::dayBegin($timestamp);

        $isShow = ($item['ShowID'] == $showId);
        $inRange = ($dayBegin <= $onair);
        return ($isShow && $inRange);
      }
    );

    return $response;
  }
}