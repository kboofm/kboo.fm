<?php
$schedule = [
  'id' => 'schedule-episode',
  'type' => 'episode',
  'data' => TemplateQuery::scheduledNext(),
];

include 'schedule-carousel.tpl.php';
