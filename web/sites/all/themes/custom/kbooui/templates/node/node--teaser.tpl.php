<?php
if ($node_teaser['image']):
  $classes = "col-sm-9 teaser-padding";
else:
  $classes = "col-sm-12";
endif;
?>


<h2 class="teaser-header">
  <a href="<?php print $node_url; ?>">
    <?php print $node_teaser['title']; ?>
  </a>
</h2>


<div class="row node-teaser">
  <?php if ($node_teaser['image']): ?>
  <div class="col-sm-3 teaser-image">
    <a href="<?php print $node_url; ?>">
      <img  src="<?php print $node_teaser['image']; ?>"
            alt="">
    </a>
  </div>
  <?php endif; ?>


  <div class="<?php print $classes; ?>">
    <div>
      <?php print $node_teaser['published_date']; ?>
    </div>


    <div>
      <span class="bold">Authored by</span>:&nbsp;

      <a href="<?php $node_teaser['author_url']; ?>"
         class="node entityreference">
        <?php print $node_teaser['author']; ?>
      </a>
    </div>


    <div class="teaser-summary">
      <?php print $node_teaser['summary']; ?>
      <a href="<?php print $node_url; ?>"
         class="btn pull-right more-link">
         Read more
      </a>
    </div>
  </div>
</div>
