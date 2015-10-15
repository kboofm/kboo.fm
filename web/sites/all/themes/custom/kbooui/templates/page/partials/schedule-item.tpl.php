<?php
if ($schedule_item):
?>
  <div>
    <a href="<?php print $schedule_item['url']; ?>">
      <?php print $schedule_item['title']; ?>
    </a>
  </div>

  <div>
    <?php print $schedule_item['start']['formatted_date']; ?>
  </div>

  <div>
    <?php print $schedule_item['start']['formatted_time']; ?> -
    <?php print $schedule_item['finish']['formatted_time']; ?>
  </div>
<?php
endif;

