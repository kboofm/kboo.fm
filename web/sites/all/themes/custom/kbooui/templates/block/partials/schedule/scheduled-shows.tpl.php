<?php
$component = new ScheduleComponent();
$data = $component->next($stream);

$timestamp = NULL;
if (isset($data[0]['start']['timestamp'])):
  $timestamp = $data[0]['start']['timestamp'];
endif;

$schedule = [
  'id' => 'schedule-episode',
  'type' => 'episode',
  'data' => $data,
  'stream' => $stream,
  'timestamp' => $timestamp,
];

include 'schedule-carousel-show.tpl.php';
