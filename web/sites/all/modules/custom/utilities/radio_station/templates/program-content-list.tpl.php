<div class="margin-vertical-lg">
  <?php
#see radio_station_preprocess_radio_template_program_content_list in radio_station.module
if($already_rendered)
{
	print $pager;
}
else
{

  $last = count($pager['items']) - 1;
  foreach ($pager['items'] as $index => $item):
    $view = node_view($item, 'teaser');
    print drupal_render($view);

    if ($index != $last):
      print "<hr />";
    endif;
  endforeach;

  if (isset($content_url)):
    ?>
    <h4>
      <a href="<?php print $content_url; ?>">
        View latest content for <?php print $program['title']; ?>
      </a>
    </h4>
    <?php
  endif;
}
  ?>
</div>
