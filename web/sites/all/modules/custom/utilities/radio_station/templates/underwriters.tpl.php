<div class="row margin-vertical-lg">
  <div class="col-sm-12">
    <?php
    $last = count($sponsors) - 1;
    foreach ($sponsors as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;
    ?>
  </div>
</div>

