<div>
  Next up:
  <ul>
    <?php
    $programs = TemplateQuery::scheduledNext(2);
    foreach ($programs as $program):
      ?>
      <li>
        <?php
        print "{$program['title']} - {$program['start']}";
        ?>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
