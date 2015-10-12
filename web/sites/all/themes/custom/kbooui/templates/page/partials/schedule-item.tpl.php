<?php
if ($schedule_item):
?>
  <a href="<?php print $schedule_item['program']['url']; ?>">
    <?php print $schedule_item['program']['title']; ?>
  </a>
<?php
else:
  print "Nothing airing";
endif;

