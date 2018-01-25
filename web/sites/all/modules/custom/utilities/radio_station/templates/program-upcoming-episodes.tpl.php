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

<div class="well">
  <h3>
    Coming Soon
  </h3>

  <div class="margin-vertical-lg">
    <?php foreach ($upcoming as $index => $item): ?>
      <?php if ($item["starttime"]): ?>
        <div>
	<?php if(isset($item['url'])): ?>
          <a href="<?php print $item["url"]; ?>">
	<?php endif; ?>
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

            if (isset($item['ends_different_day']) && $item['ends_different_day']):
              $end_day = Helpers::toCarbonString(
                $formats['date'],
                $item['endtime']
              );

              print " - {$end_day} at {$end_time}";

            elseif ($start_time != $end_time):
              print " - {$end_time}";
            endif;
          ?>
	<?php if(isset($item['url'])): ?>
          </a>
	<?php endif; ?>
        </div>
      <?php endif; ?>


      <div>
        <?php if(isset($item['summary'])) { print $item['summary']; } ?>
      </div>


      <?php
        if ($index != $last):
          print "<hr />";
        endif;
      ?>
    <?php endforeach; ?>
  </div>
</div>

