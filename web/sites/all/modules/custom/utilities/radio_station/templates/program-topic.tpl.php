<ul class="nav nav-tabs margin-vertical-lg" role="tablist">
  <li role="presentation">
    <a href="/program" role="tab">All Programs</a>
  </li>

  <li role="presentation">
    <a href="/program/genre" role="tab">Programs by Genre</a>
  </li>

  <li role="presentation" class="active">
    <a href="/program/topic" role="tab">Programs by Topic</a>
  </li>
</ul>


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
