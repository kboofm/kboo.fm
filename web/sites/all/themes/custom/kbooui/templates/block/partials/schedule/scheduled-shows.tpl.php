<?php
$component = new ScheduleComponent();
$data = $component->next($stream);

$timestamp = NULL;
$datetime = NULL;
if (isset($data[0]['start']['timestamp'])):
  $start = $data[0]['start'];
  $timestamp = $start['timestamp'];
  $datetime = $start['formatted_date'] . ' ' . $start['formatted_time'];
endif;

$schedule = [
  'id' => 'schedule-episode',
  'type' => 'episode',
  'data' => $data,
  'stream' => $stream,
  'timestamp' => $timestamp,
  'datetime' => $datetime,
];

include 'schedule-carousel-show.tpl.php';
