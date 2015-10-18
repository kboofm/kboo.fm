<?php
$schedule = [
  'id' => 'schedule-day',
  'type' => 'day',
  'data' => TemplateQuery::scheduledToday(),
];
include 'schedule-carousel.tpl.php';
