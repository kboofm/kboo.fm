<?php

/**
 * Implements hook_drush_command().
 */
function radio_station_drush_command() {
  $ccs_example = [
    'key' => 'drush schedule-cache-clear --min=-1 --max=1',
    'value' => 'Clears schedule cache for last week, this week, and next week',
  ];

  $cgs_example = [
    'key' => 'drush schedule-cache-generate --min=-1 --max=1',
    'value' => 'Generates schedule cache for last week, this week, and next week',
  ];

  $items['schedule-cache-clear-all'] = [
    'description' => 'Clear all schedule cache',
    'aliases' => ['sch-cca'],
  ];

  $items['schedule-cache-clear'] = [
    'description' => 'Clear the schedule cache',
    'aliases' => ['sch-cc'],
    'options' => [
      'min' => 'Minimum week',
      'max' => 'Maximum week',
    ],
    'examples' => [
      $ccs_example['key'] => $ccs_example['value'],
    ],
  ];

  $items['schedule-cache-generate'] = [
    'description' => 'Generate the schedule cache',
    'aliases' => ['sch-cg'],
    'options' => [
      'min' => 'Minimum week',
      'max' => 'Maximum week',
    ],
    'examples' => [
      $cgs_example['key'] => $cgs_example['value'],
    ],
  ];

  $items['schedule-cache-list'] = [
    'description' => 'List the schedule cache keys',
    'aliases' => ['sch-cl'],
  ];

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
 * Callback for the cache-clear-schedule-all command
 */
function drush_radio_station_schedule_cache_clear_all() {
  $cache = new ScheduleCache();
  $cache->forceClear();
}


/**
 * Callback for the cache-clear-schedule command
 */
function drush_radio_station_schedule_cache_clear() {
  $min = (int)drush_get_option("min");
  $max = (int)drush_get_option("max");

  if ($max < $min) {
    $temp = $min;
    $min = $max;
    $max = $temp;
  }

  $cache = new ScheduleCache();
  $cache->clearWeeks($min, $max);
}


/**
 * Callback for the cache-generate-schedule command
 */
function drush_radio_station_schedule_cache_generate() {
  $min = (int)drush_get_option("min");
  $max = (int)drush_get_option("max");

  if ($max < $min) {
    $temp = $min;
    $min = $max;
    $max = $temp;
  }

  $component = new ScheduleComponent();
  $component->getWeeks($min, $max);
}


/**
 * Callback for the cache-list-schedule command
 */
function drush_radio_station_schedule_cache_list() {
  $cache = new ScheduleCache();
  $results = db_select($cache->table, "c")
    ->fields("c", ["cid"])
    ->execute()
    ->fetchAllKeyed();

  $keys = array_keys($results);
  array_walk(
    $keys,
    function ($item) {
      $parts = explode("_", $item);
      $last = end($parts);
      $datetime = date("Y-m-d", $last);

      print "{$datetime} - {$item}" . PHP_EOL;
    }
  );
}
