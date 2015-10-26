<?php
$component = new ScheduleComponent();
$data = $component->today($stream);

$timestamp = NULL;
$datetime = NULL;
if (isset($data[0]['start']['timestamp'])):
  $start = $data[0]['start'];
  $timestamp = $start['timestamp'];
  $datetime = $start['formatted_date'];
endif;

$schedule = [
  'id' => 'schedule-day',
  'type' => 'day',
  'stream' => $stream,
  'data' => $data,
  'timestamp' => $timestamp,
  'datetime' => $datetime,
];

include 'schedule-carousel-day.tpl.php';
