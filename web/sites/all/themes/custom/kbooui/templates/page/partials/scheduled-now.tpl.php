<?php
$schedule_item = TemplateQuery::scheduledNow();
$schedule = [$schedule_item];
$schedule = [
  'data' => [$schedule_item],
  'timestamp' => $schedule_item['start']['timestamp'],
];
?>

<h4>On now:</h4>

<?php if ($schedule_item): ?>
  <div class="row">
    <div class="col-md-4">
      <?php
      $data_items = $schedule['data'];
      include 'schedule-list.tpl.php';
      ?>
    </div>
  </div>
<?php else: ?>
  Nothing airing
<?php endif; ?>
