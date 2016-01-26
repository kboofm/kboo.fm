<h4 class="text-center margin-top-lg">
  Events for <?php print $display_date; ?>
</h4>


<div class="row margin-vertical-md">
  <div class="col-md-10 col-md-offset-1 well">
    <p class="">
      NOTE: When narrowing down the list for on-air,
      please eliminate events with a rating of 3 first,
      then events with a rating of 2.
    </p>


    <p class="margin-vertical-md">
      Events that are
      <span class="livewire-override">highlighted</span>
      have been marked as "Always Include"
      via the Livewire Script Override.
    </p>


    <p class="">
      Events for today includes events between 7am - 6:59am the next day.
      Events for tomorrow includes events between 7am - 12noon the next day.
    </p>
  </div>
</div>


<form id="livewire-script-form"
      action=''
      method='get'>

  <?php if (isset($day_events)): ?>
    <div class="panel panel-default">
      <div class="panel-heading">
        <h3 class="panel-title">
          Day's Events
        </h3>
      </div>

      <div class="panel-body">
        <?php
          foreach ($day_events as $event):
            $checkbox_name = "day-nids";
            include 'script-form-event.tpl.php';
          endforeach;
        ?>
      </div>
    </div>
  <?php endif; ?>


  <?php if (isset($next_day_events)): ?>
    <div class="panel panel-default">
      <div class="panel-heading">
        <h3 class="panel-title">
          Next day's Events
        </h3>
      </div>

      <div class="panel-body">
        <?php
        foreach ($next_day_events as $event):
          $checkbox_name = "next-day-nids";
          include 'script-form-event.tpl.php';
        endforeach;
        ?>
      </div>
    </div>
  <?php endif; ?>

  <div class="text-center margin-top-lg">
    <span data-bind="events-count">
      <?php print $total_count; ?>
    </span>
    events selected
  </div>


  <div class="row margin-vertical-lg">
    <div class="col-md-4 col-md-offset-4">
      <button type="submit"
              id="btn-submit"
              class="btn btn-default">
        Generate a script from these results
      </button>
    </div>
  </div>


  <input type="hidden"
         name="phase"
         value="<?php print ELivewireRoutePhase::GeneratedScript; ?>">


  <input type="hidden"
         name="lead-params"
         value="<?php print $lead_params; ?>">
</form>
