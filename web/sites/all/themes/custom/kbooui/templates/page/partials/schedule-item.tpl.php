<?php
if ($schedule_item):
?>
  <div data-bind="schedule-item">
    <a data-bind="title-link"
       href="<?php print $schedule_item['url']; ?>">
      <?php print $schedule_item['title']; ?>
    </a>

    <div data-bind="formatted-date">
      <?php print $schedule_item['start']['formatted_date']; ?>
    </div>

    <div data-bind="formatted-time">
      <span data-bind="start-time">
        <?php print $schedule_item['start']['formatted_time']; ?>
      </span>

      -

      <span data-bind="finish-time">
        <?php print $schedule_item['finish']['formatted_time']; ?>
      </span>
    </div>
  </div>
<?php
endif;
