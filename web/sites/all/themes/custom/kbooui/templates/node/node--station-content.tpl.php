<div id="node-<?php print $node->nid; ?>"
     class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>


  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>


  <div class="content"<?php print $content_attributes; ?>>
    <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content);
    ?>
  </div>


<?php
	$ppl = TRUE;
	if(isset($variables['field_produced_for'][0]['target_id']))
	{
		$pf = $variables['field_produced_for'][0]['target_id'];
		$pf = node_load($pf);
		if(isset($pf->field_streams['und'][0]['target_id']))
		{
			$stream = $pf->field_streams['und'][0]['target_id'];
			#49107 is bootwo / podcasts
			#44648 is kboo stream 1
			#hardcoded now as these are our only choices
			if($stream == 49107)
			{
				$ppl = FALSE;
			}
		}
	}
	if($ppl)
	{
		print theme('radio_template_episode_playlists');
	}
?>


  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>
</div>
