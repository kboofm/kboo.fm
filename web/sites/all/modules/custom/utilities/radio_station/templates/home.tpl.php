<div class="row margin-vertical-none">
  <div class="col-sm-12">
    <?php
    $last = count($items) - 1;
    foreach ($items as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;
    ?>
  </div>
</div>
