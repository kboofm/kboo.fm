<div>
  This Week:
  <ul>
    <?php
    $schedule = TemplateQuery::scheduledThisWeek();
    foreach ($schedule as $schedule_item):
      ?>
      <li>
        <?php include 'schedule-item.tpl.php'; ?>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
