<?php
$schedule_group = TemplateQuery::scheduledNextWeek();
?>

<br />
<?php foreach ($schedule_group as $dayOfWeek => $schedule): ?>
  <?php if ($schedule): ?>
    <h5><?php print $dayOfWeek; ?></h5>
    
    <div class="row">
      <div class="col-md-4">
        <?php include 'schedule-list.tpl.php'; ?>
      </div>
    </div>
  <?php endif; ?>
<?php endforeach; ?>
