<?php

/**
 * Implements hook_drush_command().
 */
function radio_station_drush_command() {
  $examples = [
    'clear' => [
      'key' => 'drush schedule-cache-clear --min=-1 --max=1',
      'value' => 'Clears schedule cache for last week, this week, and next week',
    ],

    'clear-stream' => [
      'key' => 'drush schedule-cache-clear-stream --stream=one',
      'value' => 'Clears schedule cache for the specified stream',
    ],

    'generate' => [
      'key' => 'drush schedule-cache-generate --min=-1 --max=1',
      'value' => 'Generates schedule cache for last week, this week, and next week',
    ],

    'refresh' => [
      'key' => 'drush schedule-cache-refresh --min=-1 --max=1',
      'value' => 'Refresh schedule cache for last week, this week, and next week',
    ],
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
      $examples['clear']['key'] => $examples['clear']['value'],
    ],
  ];

  $items['schedule-cache-clear-stream'] = [
    'description' => 'Clear the schedule cache for the given stream',
    'aliases' => ['sch-ccs'],
    'options' => [
      'stream' => 'Stream',
    ],
    'examples' => [
      $examples['clear-stream']['key'] => $examples['clear-stream']['value'],
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
      $examples['generate']['key'] => $examples['generate']['value'],
    ],
  ];

  $items['schedule-cache-list'] = [
    'description' => 'List the schedule cache keys',
    'aliases' => ['sch-cl'],
  ];

  $items['schedule-cache-refresh'] = [
    'description' => 'Refresh the schedule cache',
    'aliases' => ['sch-cr'],
    'options' => [
      'min' => 'Minimum week',
      'max' => 'Maximum week',
    ],
    'examples' => [
      $examples['refresh']['key'] => $examples['refresh']['value'],
    ],
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
 * Callback for the schedule-cache-clear-all command
 */
function drush_radio_station_schedule_cache_clear_all() {
  $cache = new ScheduleCache();
  $cache->forceClear();
}


/**
 * Callback for the schedule-cache-clear-stream command
 */
function drush_radio_station_schedule_cache_clear_stream() {
  $stream = drush_get_option("stream");

  if (!$stream) {
    $stream = EStreams::One;
  }

  $cache = new ScheduleCache();
  $cache->forceClear($stream);
}


/**
 * Callback for the schedule-cache-clear command
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


/**
 * Callback for the cache-refresh-schedule command
 */
function drush_radio_station_schedule_cache_refresh() {
  drush_radio_station_schedule_cache_clear();
  drush_radio_station_schedule_cache_generate();
}
