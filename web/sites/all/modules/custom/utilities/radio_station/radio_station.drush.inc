<?php

/**
 * Implements hook_drush_cache_clear().
 * @param $types
 */
function radio_station_drush_cache_clear(&$types) {
  $types['radio_station_latest_audio'] = '_radio_station_latest_audio_cache_clear';
  $types['radio_station_latest_playlists'] = '_radio_station_latest_playlists_cache_clear';
}


function _radio_station_latest_audio_cache_clear() {
  $cache_table = "cache_radio_station";
  cache_clear_all("radio_station_latest_audio", $cache_table);
}


function _radio_station_latest_playlists_cache_clear() {
  $cache_table = "cache_radio_station";
  cache_clear_all("radio_station_latest_playlists", $cache_table);
}
