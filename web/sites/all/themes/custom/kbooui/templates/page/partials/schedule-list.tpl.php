<ul class="list-group"
  data-bind="schedule-items">
  <?php foreach ($data_items as $schedule_item): ?>
    <?php include 'schedule-list-item.tpl.php'; ?>
  <?php endforeach; ?>
</ul>
