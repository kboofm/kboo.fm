<?php

/**
 * Implements hook_drush_command().
 */
function radio_station_drush_command() {
  $items['cache-clear-schedule'] = array(
    'description' => 'Clear the schedule cache',
    'aliases' => array('ccs'),
  );

  return $items;
}


/**
 * Implements hook_drush_cache_clear().
 * @param $types
 */
function radio_station_drush_cache_clear(&$types) {
  $types['radio_station_latest_audio'] = '_radio_station_latest_audio_cache_clear';
  $types['radio_station_latest_playlists'] = '_radio_station_latest_playlists_cache_clear';
}


function _radio_station_latest_audio_cache_clear() {
  $cache = new SidebarCache();
  $cache->forceClear("audio");
}


function _radio_station_latest_playlists_cache_clear() {
  $cache = new SidebarCache();
  $cache->forceClear("playlists");
}


/**
 * Callback for the cache-clear-schedule command
 */
function drush_radio_station_cache_clear_schedule() {
  $stream = EStreams::One;
  $cache = new ScheduleCache();
  $cache->forceClear($stream);
}
