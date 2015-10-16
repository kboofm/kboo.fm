<?php
if ($schedule_item):
?>
  <div data-bind="schedule-item">
    <a data-bind="title-link"
       href="<?php print $schedule_item['url']; ?>">
      <?php print $schedule_item['title']; ?>
    </a>

    <div class="formatted-date">
      <?php print $schedule_item['start']['formatted_date']; ?>
    </div>

    <div class="formatted-time">
      <?php print $schedule_item['start']['formatted_time']; ?> -
      <?php print $schedule_item['finish']['formatted_time']; ?>
    </div>
  </div>
<?php
endif;
