<div>
  Today:
  <ul>
    <?php
    $schedule = TemplateQuery::scheduledToday();
    foreach ($schedule as $schedule_item):
      ?>
      <li>
        <?php include 'schedule-item.tpl.php'; ?>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
