<div class="row margin-top">
  <div class="col-md-1 padding-vertical-lg schedule-carousel-prev">
    Previous
  </div>


  <div class="col-md-4 schedule-carousel-content"
       data-timestamp="<?php print $schedule[0]['start']['timestamp']; ?>">

    <?php include 'schedule-list.tpl.php'; ?>
  </div>


  <div class="col-md-1 padding-vertical-lg schedule-carousel-next">
    Next
  </div>
</div>
