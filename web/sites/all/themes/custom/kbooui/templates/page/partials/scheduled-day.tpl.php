<?php
$data = TemplateQuery::scheduledToday();

$schedule = [
  'id' => 'schedule-day',
  'type' => 'day',
  'data' => $data,
  'timestamp' => $data[0]['start']['timestamp'],
];
include 'schedule-carousel-day.tpl.php';
