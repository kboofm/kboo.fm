<?php
if ($schedule_item):
?>
  <div>
    <a class="schedule-item-title-link"
       href="<?php print $schedule_item['url']; ?>">
      <?php print $schedule_item['title']; ?>
    </a>
  </div>

  <div class="schedule-item-formatted-date">
    <?php print $schedule_item['start']['formatted_date']; ?>
  </div>

  <div class="schedule-item-formatted-time">
    <?php print $schedule_item['start']['formatted_time']; ?> -
    <?php print $schedule_item['finish']['formatted_time']; ?>
  </div>
<?php
endif;
