<ul class="nav nav-tabs margin-vertical-lg" role="tablist">
  <li role="presentation">
    <a href="/live-events" role="tab">Upcoming</a>
  </li>

  <li role="presentation" class="active">
    <a href="/live-events/previous" role="tab">Previous</a>
  </li>
</ul>


<?php
$last = count($pager['events']) - 1;
foreach ($pager['events'] as $index => $event):
  $view = node_view($event, 'teaser');
  print drupal_render($view);

  if ($index != $last):
    print "<hr />";
  endif;
endforeach;

include 'partials/pager.tpl.php';
