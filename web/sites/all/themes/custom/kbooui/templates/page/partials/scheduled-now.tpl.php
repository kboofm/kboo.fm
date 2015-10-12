<div>
  On now:
  <?php
  $schedule_item = TemplateQuery::scheduledNow();
  ?>

  <?php
  include 'schedule-item.tpl.php';
  ?>
</div>
