<div class="panel panel-default">
  <div class="panel-heading">
    <h3 class="panel-title">
      <a href="<?php print $venue['url']; ?>">
        <?php print $venue['title']; ?>
      </a>  
    </h3>
  </div>

  <div class="panel-body">
    <?php $last = count($venue['events']) - 1; ?>
    <?php foreach ($venue['events'] as $index => $event): ?>
        <?php include 'livewire-calendar-event.tpl.php' ?>
    <?php endforeach; ?>
  </div>
</div>
