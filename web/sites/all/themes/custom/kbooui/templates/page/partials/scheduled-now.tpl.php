<?php
$schedule_item = TemplateQuery::scheduledNow();
$schedule = [$schedule_item];
?>

<h4>On now:</h4>

<?php if ($schedule[0]): ?>
  <div class="row">
    <div class="col-md-4">
      <?php include 'schedule-list.tpl.php'; ?>
    </div>
  </div>
<?php else: ?>
  Nothing airing
<?php endif; ?>
