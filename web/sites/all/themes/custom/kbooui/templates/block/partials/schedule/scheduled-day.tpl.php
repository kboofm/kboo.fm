<?php
$component = new ScheduleComponent();
$data = $component->today($stream);

$timestamp = NULL;
if (isset($data[0]['start']['timestamp'])):
  $timestamp = $data[0]['start']['timestamp'];
endif;

$schedule = [
  'id' => 'schedule-day',
  'type' => 'day',
  'stream' => $stream,
  'data' => $data,
  'timestamp' => $timestamp,
];

include 'schedule-carousel-day.tpl.php';
