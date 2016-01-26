<div class="row margin-top-lg livewire-venues">
  <div class="col-sm-12">
    <?php include 'partials/venues-form.tpl.php'; ?>

    <?php include 'partials/pager-alphabetic.tpl.php'; ?>

    <ul class="margin-vertical-lg venue-list">
      <?php foreach ($pager['venues'] as $venue): ?>
        <li class="venue">
          <a href="<?php print $venue['url']; ?>">
            <?php print $venue['title']; ?>
          </a>
        </li>
      <?php endforeach; ?>
    </ul>

    <?php
    include 'partials/pager.tpl.php';
    ?>
  </div>
</div>
