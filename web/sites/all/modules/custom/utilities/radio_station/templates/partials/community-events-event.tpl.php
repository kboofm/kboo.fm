<?php
$formats = [
  'month' => 'M',
  'day' => 'j',
  'date' => 'l,  F j',
  'time' => 'g:ia',
];
?>


<div class="row">
  <div class="col-xs-2 calendar-page">
    <div class="month">
      <?php
      print Helpers::toCarbonString(
        $formats['month'],
        $event['starttime']
      );
      ?>
    </div>

    <div class="day">
      <?php
      print Helpers::toCarbonString(
        $formats['day'],
        $event['starttime']
      );
      ?>
    </div>

    <?php if ($event['ends_different_day']): ?>
      <div class="small">
        until
      </div>

      <div class="month margin-top-xs">
        <?php
        print Helpers::toCarbonString(
          $formats['month'],
          $event['endtime']
        );
        ?>
      </div>

      <div class="day">
        <?php
        print Helpers::toCarbonString(
          $formats['day'],
          $event['endtime']
        );
        ?>
      </div>
    <?php endif; ?>
  </div>


  <div class="col-xs-10 calendar-info">
    <p class="truncate">
      <a href="<?php print $event['url']; ?>">
        <?php print $event['title']; ?>
      </a>
    </p>

    <div>
      <?php
        $start_day = Helpers::toCarbonString(
          $formats['date'],
          $event['starttime']
        );

        $start_time = Helpers::toCarbonString(
          $formats['time'],
          $event['starttime']
        );

        $end_time = Helpers::toCarbonString(
          $formats['time'],
          $event['endtime']
        );

        print "{$start_day} at {$start_time} - ";

        if ($event['ends_different_day']):
          $end_day = Helpers::toCarbonString(
            $formats['date'],
            $event['endtime']
          );

          print "{$end_day} at ";
        endif;

        print $end_time;
      ?>
    </div>

    <p class="truncate">
      Venue: <?php print $event['venue_location_name']; ?>
    </p>

  </div>
</div>

<?php if ($index != $last): ?>
  <hr />
<?php endif; ?>