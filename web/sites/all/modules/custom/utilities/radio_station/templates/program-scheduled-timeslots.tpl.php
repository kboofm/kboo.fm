<?php
$formats = [
  'weekday' => 'l',
  'time' => 'g:ia',
];


?>

<?php foreach ($timeslots as $timeslot): ?>
  <?php
    $weekday = Helpers::toCarbonString(
      $formats['weekday'],
      $timeslot['starttime']
    );

    $start = Helpers::toCarbonString(
      $formats['time'],
      $timeslot['starttime']
    );

    $end = Helpers::toCarbonString(
      $formats['time'],
      $timeslot['endtime']
    );

    $frequency = strtolower(
      $timeslot['frequency']
    );

    $stream = $timeslot['stream'];
  ?>

  <div>
    <?php print "{$weekday} at {$start} - {$end}, repeats {$frequency} on {$stream}"; ?>
  <div>
<?php endforeach;
