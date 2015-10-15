<?php
$schedule_item = TemplateQuery::scheduledNow();
$schedule = [$schedule_item];
?>
<h4>On now:</h4>
<?php include 'schedule-list.tpl.php'; ?>
