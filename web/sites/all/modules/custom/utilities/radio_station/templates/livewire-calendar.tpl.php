<div class="livewire-calendar">
  <div class="row margin-bottom-lg margin-top-md margin-horizontal-none">
    <div class="col-xs-1 livewire-sort-arrows">
      <a href="<?php print "?date={$prev_date}"; ?>">
        <i class="fa fa-arrow-left"></i>
      </a>
    </div>


    <div class="col-xs-10 text-center">
      <span class="livewire-sort-heading">
        Events by venue for
        <span class="heading-date">
          <?php print $heading_date; ?>
        </span>
      </span>
    </div>


    <div class="col-xs-1 pull-right livewire-sort-arrows">
      <a href="<?php print "?date={$next_date}"; ?>">
        <i class="fa fa-arrow-right"></i>
      </a>
    </div>
  </div>


  <div class="row">
    
    <div class="margin-bottom-lg col-md-5 col-md-push-7 livewire-sidebar">
      <div class="text-center">
        <div class="panel panel-default">
          <div class="panel-body">
            <div id="livewire-calendar-widget"
                 data-current-date="<?php print $current_date; ?>"></div>

            <p class="margin-top-md">
              Find events by

              <a href="new-orleans-community/music-venues">
                Music Venue
              </a>

              or do a

              <a href="search/node">
                Sitewide Search
              </a>
            </p>

            <hr/>

            <p>
              <a href="new-orleans-community/submit-your-event">
                Submit your music events
              </a>
            </p>

            <hr/>

            <p>
              * The Livewire music listings are aired every odd hour on WWOZ.
              <br/>
              <a href="new-orleans-community/music-calendar-policy">
                Music calendar policy
              </a>
            </p>
          </div>
        </div>
      </div>
    </div>

    <div class="margin-bottom-lg col-md-7 col-md-pull-5 livewire-listing">
      <div class="">
          <?php foreach ($venues as $venue): ?>
              <?php include 'partials/livewire-calendar-venue.tpl.php'; ?>
          <?php endforeach; ?>
      </div>
    </div>

  </div>
</div>
