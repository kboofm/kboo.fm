<div class="margin-vertical-lg">
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
