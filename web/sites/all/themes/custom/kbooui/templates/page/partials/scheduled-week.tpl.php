<?php
$data = TemplateQuery::scheduledThisWeek();
$firstDayOfWeek = reset($data);

$schedule = [
  'id' => 'schedule-week',
  'type' => 'week',
  'data' => $data,
  'timestamp' => $firstDayOfWeek[0]['start']['timestamp'],
];
include 'schedule-carousel-week.tpl.php';
