<?php
$schedule_group = TemplateQuery::scheduledThisWeek();
?>

<h4>This Week:</h4>
<?php foreach ($schedule_group as $dayOfWeek => $schedule): ?>
  <?php if ($schedule): ?>
    <h5><?php print $dayOfWeek; ?></h5>
    <?php include 'schedule-list.tpl.php'; ?>
  <?php endif; ?>
<?php endforeach; ?>
