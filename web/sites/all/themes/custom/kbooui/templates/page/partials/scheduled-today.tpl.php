<?php
$schedule = TemplateQuery::scheduledToday();
?>

<div class="row margin-top">
  <div class="col-md-4">
    <?php include 'schedule-list.tpl.php'; ?>
  </div>
</div>
