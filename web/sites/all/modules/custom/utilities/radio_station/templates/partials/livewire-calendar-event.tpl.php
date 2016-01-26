<?php
$formats = [
  'month' => 'M',
  'day' => 'j',
  'date' => 'l,  F j',
  'time' => 'g:ia',
];

$prev = null;
?>


<div class="row">
  <div class="col-xs-2 calendar-page">
    <?php if ($event['starttime'] != $prev): ?>
    <div class="month">
      <?php
      $prev = $event['starttime'];
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
    <?php endif; ?>
  </div>


  <div class="col-xs-10 calendar-info">
    <p class="truncate">
      <a href="<?php print $event['url']; ?>">
        <?php print $event['title']; ?>
      </a>
    </p>

    <p>
      <?php
      print Helpers::toCarbonString(
        $formats['date'],
        $event['starttime']
      );
      ?>

      at

      <?php
      print Helpers::toCarbonString(
        $formats['time'],
        $event['starttime']
      );
      ?>
    </p>

    <?php if ($index != $last): ?>
      <hr />
    <?php endif; ?>
  </div>
</div>
