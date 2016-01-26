<div class="row margin-vertical-lg">
  <div class="col-sm-12">
    <p class="margin-bottom-lg">
      WWOZ brings together our local, national and international supporters into a distinctive community that celebrates and strengthens the music, musicians, culture and culture bearers of New Orleans.
    </p>


    <?php
    $last = count($pager['items']) - 1;
    foreach ($pager['items'] as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;

    include 'partials/pager.tpl.php';
    ?>
  </div>
</div>