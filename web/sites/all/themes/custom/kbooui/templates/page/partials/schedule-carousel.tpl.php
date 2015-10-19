<div class="row margin-top">
  <div class="col-md-1 schedule-carousel-prev"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-left cursor-pointer"></i>
  </div>


  <div class="col-md-1 schedule-carousel-next"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-right cursor-pointer"></i>
  </div>
</div>


<div class="row margin-top">
  <div id="<?php print $schedule['id']; ?>"
       class="col-md-4 schedule-carousel"
       data-type="<?php print $schedule['type']; ?>">

    <div class="schedule-carousel-timestamp"
         data-timestamp="<?php print $schedule['timestamp']; ?>">

      <?php if ($schedule['type'] == 'week'): ?>
        <?php foreach ($schedule['data'] as $dayOfWeek => $data_items): ?>
          <h4><?php print $dayOfWeek; ?></h4>
          <?php include 'schedule-list.tpl.php'; ?>
        <?php endforeach; ?>
      <?php else:
        $data_items = $schedule['data'];
        include 'schedule-list.tpl.php';
      endif; ?>

    </div>
  </div>
</div>
