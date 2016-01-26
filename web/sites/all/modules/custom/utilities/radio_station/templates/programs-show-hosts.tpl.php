<div class="row">
  <div class="col-sm-12 show-hosts">
    <?php include 'partials/programs-show-hosts-form.tpl.php'; ?>
    <?php include 'partials/pager-alphabetic.tpl.php'; ?>


    <?php foreach ($profiles as $key => $data): ?>
      <h4 id="<?php print $key; ?>">
        <?php print $key; ?>
      </h4>


      <ul class="show-host-list">
        <?php foreach ($data as $profile): ?>
          <li>
            <a href="<?php print $profile['url']; ?>">
              <?php print $profile['title']; ?>
            </a>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endforeach; ?>


    <?php include 'partials/pager-alphabetic.tpl.php'; ?>
  </div>
</div>


