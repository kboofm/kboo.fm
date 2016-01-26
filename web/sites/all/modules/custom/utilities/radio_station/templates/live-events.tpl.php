<ul class="nav nav-tabs margin-top-lg" role="tablist">
  <li role="presentation" class="active">
    <a href="/live-events" role="tab">Upcoming</a>
  </li>

  <li role="presentation">
    <a href="/live-events/previous" role="tab">Previous</a>
  </li>
</ul>


<?php
$last = count($events) - 1;
foreach ($events as $index => $event):
  $view = node_view($event);
  print drupal_render($view);

  if ($index != $last) {
    print "<hr />";
  }
endforeach;
