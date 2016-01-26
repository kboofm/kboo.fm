<div class="row">
  <div class="col-sm-12">
    <p class="margin-top-lg">
      Below are upcoming single-day Community Events in and around New Orleans.
      For events with multiple dates please see our Ongoing Events page.
    </p>


    <p>
      Non-Profit Organizations: WWOZ broadcasts PSAs on-air in our
      "Community Notebook" segment. If you would like us to consider
      including your event, please submit a brief description of your
      organization, the details of your event and proof of 501(c) 3
      status to help@wwoz.org. We recommend submitting your request
      at least 3 weeks in advance.
    </p>
  </div>
</div>


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
