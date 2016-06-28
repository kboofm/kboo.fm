<?php
$active_tab = "genre";
include "partials/program-tabs.tpl.php";
?>


<?php foreach ($genres as $genre => $programs): ?>
  <h3>
    <?php print $genre; ?>
  </h3>


  <ul>
    <?php foreach ($programs as $program): ?>
    <li>
      <a href="<?php print $program['url']; ?>">
        <?php print $program['title']; ?>
      </a>
    </li>
    <?php endforeach; ?>
  </ul>
<?php endforeach; ?>
