<?php
$formats = [
  'date' => 'D, m/d/Y',
  'time' => 'g:ia',
];

if ($node_teaser["image"]):
  $classes = "col-md-9 teaser-padding";
else:
  $classes = "col-md-12";
endif;
?>


<h2 class="teaser-header">
  <a href="<?php print $node_url; ?>">
    <?php print $node_teaser["title"]; ?>
  </a>
</h2>


<div class="row node-teaser">
  <?php if ($node_teaser["image"]): ?>
  <div class="col-md-3 teaser-image">
    <a href="<?php print $node_url; ?>">
      <img  src="<?php print $node_teaser["image"]; ?>"
            alt="">
    </a>
  </div>
  <?php endif; ?>


  <div class="<?php print $classes; ?>">
    <?php if ($node_teaser["starttime"]): ?>
      <div>
        Airs at:

        <?php
          $start_day = Helpers::toCarbonString(
            $formats['date'],
            $node_teaser['starttime']
          );

          $start_time = Helpers::toCarbonString(
            $formats['time'],
            $node_teaser['starttime']
          );

          $end_time = Helpers::toCarbonString(
            $formats['time'],
            $node_teaser['endtime']
          );

          print "{$start_day} at {$start_time}";

          if ($node_teaser['ends_different_day']):
            $end_day = Helpers::toCarbonString(
              $formats['date'],
              $node_teaser['endtime']
            );

            print " - {$end_day} at {$end_day}";

          elseif ($start_time != $end_time):
            print " - {$end_time}";
          endif;
        ?>
      </div>
    <?php endif; ?>


    <?php if ($node_teaser["produced_for"]): ?>
      <div>
        <span class="bold">Produced for</span>:&nbsp;
        <?php $last = count($node_teaser["produced_for"]) - 1; ?>
        <?php foreach ($node_teaser["produced_for"] as $index => $program): ?>
        <a href="<?php print $program["url"]; ?>"
           class="node entityreference">
          <?php print $program["title"]; ?></a><?php if ($index != $last): ?>, <?php endif; ?>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>

<?php
	#nested is here and audio files are here
	#tell the field tpl that we have a nested audio situation -- ie we have to pass the audio source 
	#to the preprocessor
	if(isset($variables['elements']['#nested_audio']) && $variables['elements']['#nested_audio'])
	{
		$node_teaser['audio_files']['#nested_audio'] = TRUE;
	}
	if(isset($node_teaser['audio_files']))
	{
		print render($node_teaser['audio_files']);
	}
?>

    <div class="teaser-summary">
      <?php print $node_teaser["summary"]; ?>
      <a href="<?php print $node_url; ?>"
         class="btn pull-right more-link">
         Read more
      </a>
    </div>
  </div>
</div>
