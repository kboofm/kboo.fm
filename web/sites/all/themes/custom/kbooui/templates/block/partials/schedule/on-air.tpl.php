<?php
$stream = EStreams::One;
$component = new ScheduleComponent();
$shows = $component->getShow($stream, "at", time());
$schedule_item = array_pop($shows);

if (!$schedule_item):
  return;
endif;
?>

<p class="on-air margin-bottom-lg truncate"
   data-stream="<?php print $stream; ?>"
   data-type="on-air">

  <?php if ($schedule_item): ?>
    <span class="">
      On Air:
    </span>

    <span class="song-artist">
      <a href="<?php print $schedule_item['url']; ?>"
         class="text-capitalize"
         data-bind="title-link">
        <?php print $schedule_item['title']; ?>
      </a>

      <?php /*if ($schedule_item['showhost']['name']): ?>
        with

        <a href="<?php print $schedule_item['showhost']['url']; ?>"
           class="text-capitalize"
           data-bind="showhost-link">
          <?php print $schedule_item['showhost']['name']; ?>
        </a>
      <?php endif;*/ ?>
    </span>
  <?php endif; ?>
</p>
