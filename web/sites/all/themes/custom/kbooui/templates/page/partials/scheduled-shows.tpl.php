<?php
$data = TemplateQuery::scheduledNext();

$schedule = [
  'id' => 'schedule-episode',
  'type' => 'episode',
  'data' => $data,
  'timestamp' => $data[0]['start']['timestamp'],
];

include 'schedule-carousel.tpl.php';
