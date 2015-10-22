<?php
$component = new ScheduleComponent();
$data = $component->thisWeek($stream);

$firstDayOfWeek = reset($data);

$timestamp = NULL;
$datetime = NULL;
if (isset($firstDayOfWeek)):
  $start = $firstDayOfWeek[0]['start'];
  $timestamp = $start['timestamp'];
  $datetime = $start['formatted_date'];
endif;

$schedule = [
  'id' => 'schedule-week',
  'type' => 'week',
  'stream' => $stream,
  'data' => $data,
  'timestamp' => $timestamp,
  'datetime' => $datetime,
];

include 'schedule-carousel-week.tpl.php';
