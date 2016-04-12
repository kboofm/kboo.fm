<?php
$active_tab = "topic";
include "partials/program-tabs.tpl.php";
?>

<?php foreach ($topics as $topic => $programs): ?>
  <h3>
    <?php print $topic; ?>
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
