<div class="row margin-top">
  <div class="col-md-1 padding-vertical-lg schedule-carousel-prev"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-left cursor-pointer"></i>
  </div>


  <div id="<?php print $schedule['id']; ?>"
       class="col-md-4 schedule-carousel"
       data-type="<?php print $schedule['type']; ?>">

    <div class="schedule-carousel-timestamp"
         data-timestamp="<?php print $schedule['data'][0]['start']['timestamp']; ?>">

      <?php include 'schedule-list.tpl.php'; ?>

    </div>
  </div>


  <div class="col-md-1 padding-vertical-lg schedule-carousel-next"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-right cursor-pointer"></i>
  </div>
</div>
