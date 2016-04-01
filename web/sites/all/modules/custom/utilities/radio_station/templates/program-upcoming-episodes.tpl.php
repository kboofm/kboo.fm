<?php
$last = count($upcoming) - 1;

if ($last < 0):
  return;
endif;
?>

<div class="well">
  <h3>
    Upcoming Episodes
  </h3>

  <div class="margin-vertical-lg">
    <?php
    foreach ($upcoming as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;
    ?>
  </div>
</div>
