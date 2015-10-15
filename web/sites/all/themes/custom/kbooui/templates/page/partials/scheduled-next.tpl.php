<?php
$schedule = TemplateQuery::scheduledNext(3);
?>

<h4>Next up:</h4>
<?php include 'schedule-list.tpl.php'; ?>
