<?php if (count($alpha_pager) > 1): ?>
  <nav class="text-center margin-top-lg alphabetic">
    <ul class="pagination">
      <?php foreach ($alpha_pager as $link): ?>
        <li class="<?php if ($link['active']): ?>active<?php endif; ?>">
          <a href="<?php print $link['href']; ?>">
            <?php print $link['title']; ?>
          </a>
        </li>
      <?php endforeach; ?>
    </ul>
  </nav>
<?php endif; ?>
