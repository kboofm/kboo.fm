<?php
if ($schedule_item):
?>
  <a href="<?php print $schedule_item['url']; ?>">
    <?php print $schedule_item['title']; ?>
  </a>
  <?php print $schedule_item['start']['formatted']; ?> -
  <?php print $schedule_item['finish']['formatted']; ?>
<?php
endif;

