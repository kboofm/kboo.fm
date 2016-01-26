<ul class="margin-top-lg">
  <?php foreach ($profiles as $profile): ?>
    <li>
      <a href="<?php print $profile['url']; ?>">
        <?php print $profile['title']; ?>
      </a>
    </li>
  <?php endforeach; ?>
</ul>
