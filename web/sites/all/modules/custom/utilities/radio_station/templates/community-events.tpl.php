<div class="row margin-vertical-lg community-events">
  <div class="col-sm-10 margin-left">
    <?php
      $last = count($events) - 1;
      foreach ($events as $index => $event):
        include 'partials/community-events-event.tpl.php';
      endforeach;
    ?>
  </div>
</div>
