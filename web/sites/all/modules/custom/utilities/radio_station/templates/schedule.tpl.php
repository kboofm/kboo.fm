<?php
$theme_path = drupal_get_path('theme', 'kbooui');
$partials = "{$theme_path}/templates/block/partials";
?>

<div class="row oz-schedule">
  <div class="col-md-4 col-md-offset-4">
    <?php include "{$partials}/schedule/scheduled-now.tpl.php"; ?>
    <?php include "{$partials}/schedule/schedule-tabs.tpl.php"; ?>
  </div>
</div>

