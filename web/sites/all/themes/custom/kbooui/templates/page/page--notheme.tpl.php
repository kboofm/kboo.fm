<header id="navbar"
<?php
dpm('in no theme template');
?>
</header>


<div class="main-container container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php #print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->


  <div class="row">
    <section class="col-sm-8" id="main-body">

      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron">
          <?php print render($page['highlighted']); ?>
        </div>
      <?php endif; ?>

<div id="messages">
<?php
dpm('here');
?>
      <?php print $messages; ?>
</div>

      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>

      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>

      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php print render($page['content']); ?>
    </section>
  </div>
</div>

<footer class="footer container">
  <div class="footer-menus">
    <div class="footer-menu footer-left">
      <?php print render($page['footer_left']); ?>
    </div>

    <div class="footer-menu footer-first">
      <?php print render($page['footer_first']); ?>
    </div>

    <div class="footer-menu footer-second">
      <?php print render($page['footer_second']); ?>
    </div>

    <div class="footer-menu footer-third">
      <?php print render($page['footer_third']); ?>
    </div>

    <div class="footer-menu footer-fourth">
      <?php print render($page['footer_fourth']); ?>
    </div>
  </div>

  <?php print render($page['copyright']); ?>
</footer>

