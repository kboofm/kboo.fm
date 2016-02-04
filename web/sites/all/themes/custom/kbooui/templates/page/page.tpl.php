<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <?php if ($logo): ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
        <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>

      <?php
        include dirname(__DIR__) . "/block/partials/listen-now.tpl.php";
        include dirname(__DIR__) . "/block/partials/schedule/on-air.tpl.php";
      ?>

      <button type="button"
              class="navbar-toggle"
              data-toggle="collapse"
              data-target=".navbar-collapse">

        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
    </div>

    <?php if (!empty($primary_nav) || !empty($page['navigation'])): ?>
      <div class="navbar-collapse collapse z-top">
        <nav role="navigation">
          <?php if (!empty($primary_nav)): ?>
            <?php print render($primary_nav); ?>
          <?php endif; ?>
        </nav>
      </div>
    <?php endif; ?>

    <?php
      include dirname(__DIR__) . "/block/partials/donate-btn.tpl.php";
    ?>
  </div>
</header>

<div class="main-container container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->

  <div class="row">

    <section class="col-sm-8" id="main-body">
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
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

    <aside id="sidebar" class="col-sm-3 col-sm-offset-1" role="complementary">
      <?php if (!empty($page['sidebar'])): ?>
        <?php print render($page['sidebar']); ?>
      <?php endif; ?>
    </aside>  <!-- /#sidebar -->

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
