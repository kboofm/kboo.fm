<ul class="nav nav-tabs margin-vertical-lg" role="tablist">
  <li role="presentation" class="active">
    <a href="/program" role="tab">All Programs</a>
  </li>

  <li role="presentation">
    <a href="/program/genre" role="tab">Programs by Genre</a>
  </li>

  <li role="presentation">
    <a href="/program/topic" role="tab">Programs by Topic</a>
  </li>
</ul>


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

