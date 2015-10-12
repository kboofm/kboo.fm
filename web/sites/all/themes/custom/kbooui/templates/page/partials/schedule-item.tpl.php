<?php
if ($schedule_item):
?>
  <a href="<?php print $schedule_item['url']; ?>">
    <?php print $schedule_item['title']; ?>
  </a>
<?php
else:
  print "Nothing airing";
endif;

