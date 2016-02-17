<?php
if ($node_teaser["image"]):
  $classes = "col-md-9 teaser-padding";
else:
  $classes = "col-md-12";
endif;
?>


<h2 class="teaser-header">
  <a href="<?php print $node_url; ?>">
    <?php print $node_teaser["title"]; ?>
  </a>
</h2>


<div class="row node-teaser">
  <?php if ($node_teaser["image"]): ?>
  <div class="col-md-3 teaser-image">
    <a href="<?php print $node_url; ?>">
      <img  src="<?php print $node_teaser["image"]; ?>"
            alt="">
    </a>
  </div>
  <?php endif; ?>


  <div class="<?php print $classes; ?>">
    <div>
      Airs at:
      <?php
        print Helpers::toCarbonString(
          "Y-m-d H:i",
          $node_teaser["airs_at"]
        );
      ?>
    </div>


    <div>
      <span class="bold">Related programs</span>:&nbsp;
      <?php $last = count($node_teaser["related_programs"]) - 1; ?>
      <?php foreach ($node_teaser["related_programs"] as $index => $program): ?>
      <a href="<?php $program["url"]; ?>"
         class="node entityreference">
        <?php print $program["title"]; ?></a><?php if ($index != $last): ?>, <?php endif; ?>
      <?php endforeach; ?>
    </div>


    <div class="teaser-summary">
      <?php print $node_teaser["summary"]; ?>
      <a href="<?php print $node_url; ?>"
         class="btn pull-right more-link">
         Read more
      </a>
    </div>
  </div>
</div>
