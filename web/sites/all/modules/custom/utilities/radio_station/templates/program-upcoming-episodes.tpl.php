<?php
$last = count($upcoming) - 1;
$formats = [
  'date' => 'D, m/d/Y',
  'time' => 'g:ia',
];

if ($last < 0):
  return;
endif;
?>

<div class="well col-xs-12">
  <h3>
    Coming Soon
  </h3>

  <div class="margin-vertical-lg">
    <?php foreach ($upcoming as $index => $item): ?>
      <?php if ($item["starttime"]): ?>
        <div>
          <a href="<?php print $item["url"]; ?>">
            Airs at:

            <?php
            $start_day = Helpers::toCarbonString(
              $formats['date'],
              $item['starttime']
            );

            $start_time = Helpers::toCarbonString(
              $formats['time'],
              $item['starttime']
            );

            $end_time = Helpers::toCarbonString(
              $formats['time'],
              $item['endtime']
            );

            print "{$start_day} at {$start_time}";

            if ($item['ends_different_day']):
              $end_day = Helpers::toCarbonString(
                $formats['date'],
                $item['endtime']
              );

              print " - {$end_day} at {$end_day}";

            elseif ($start_time != $end_time):
              print " - {$end_time}";
            endif;
          ?>
          </a>
        </div>
      <?php endif; ?>


      <div>
        <?php print $item['summary']; ?>
      </div>


      <?php
        if ($index != $last):
          print "<hr />";
        endif;
      ?>
    <?php endforeach; ?>
  </div>
</div>

