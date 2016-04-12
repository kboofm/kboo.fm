<?php
  $active = [
    "current" => ($active_tab == "current") ? "active" : "",
    "retired" => ($active_tab == "retired") ? "active" : "",
    "web-only" => ($active_tab == "web-only") ? "active" : "",
    "genre" => ($active_tab == "genre") ? "active" : "",
    "topic" => ($active_tab == "topic") ? "active" : "",
  ];
?>


<ul class="nav nav-tabs margin-vertical-lg"
    role="tablist">

  <li role="presentation"
      class="<?php print $active['current']; ?>">

    <a href="/program" role="tab">Current</a>
  </li>


  <li role="presentation"
      class="<?php print $active['retired']; ?>">

    <a href="/program/retired" role="tab">Retired</a>
  </li>


  <li role="presentation"
      class="<?php print $active['web-only']; ?>">

    <a href="/program/web-only" role="tab">Web-only</a>
  </li>


  <li role="presentation"
      class="<?php print $active['genre']; ?>">

    <a href="/program/genre" role="tab">By Genre</a>
  </li>


  <li role="presentation"
      class="<?php print $active['topic']; ?>">

    <a href="/program/topic" role="tab">By Topic</a>
  </li>
</ul>
