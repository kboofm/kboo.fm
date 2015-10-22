<?php
$component = new ScheduleComponent();
$data = $component->thisWeek($stream);

$firstDayOfWeek = reset($data);

$schedule = [
  'id' => 'schedule-week',
  'type' => 'week',
  'stream' => $stream,
  'data' => $data,
  'timestamp' => $firstDayOfWeek[0]['start']['timestamp'],
];

include 'schedule-carousel-week.tpl.php';
