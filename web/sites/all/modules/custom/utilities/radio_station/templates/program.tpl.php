<?php
$active_tab = "current";
include "partials/program-tabs.tpl.php";
?>


<div class="row margin-vertical-lg">
  <div class="col-sm-12">
    <?php
    $last = count($programs) - 1;
    foreach ($programs as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;
    ?>
  </div>
</div>

