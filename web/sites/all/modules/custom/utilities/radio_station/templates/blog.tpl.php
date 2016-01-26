<div class="row margin-vertical-lg">
  <div class="col-sm-12">
    <p class="margin-bottom-lg">
      Welcome to the WWOZ Blog! This is where 'OZ staff and beloved show hosts post news, thoughts, information, and of course, music.
    </p>
    <p>
      Click on Read More to see the rest of the post and leave your own comments. Check back daily for new posts and special announcements!
    </p>


    <?php
    $last = count($pager['items']) - 1;
    foreach ($pager['items'] as $index => $item):
      $view = node_view($item, 'teaser');
      print drupal_render($view);

      if ($index != $last):
        print "<hr />";
      endif;
    endforeach;

    include 'partials/pager.tpl.php';
    ?>
  </div>
</div>


