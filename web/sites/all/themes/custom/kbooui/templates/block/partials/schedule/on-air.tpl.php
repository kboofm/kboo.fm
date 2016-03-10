<?php
$stream = EStreams::One;
$component = new ScheduleComponent();
$schedule_item = $component->now($stream);
?>

<p class="on-air margin-bottom-lg truncate"
   data-stream="<?php print $stream; ?>"
   data-type="on-air">

  <?php //if ($schedule_item): ?>
    <span class="">
      On Air: 
    </span>

    <span class="song-artist">
      <a href="/media/45469-world-beat-connection-031016" class="text-capitalize" data-bind="title-link">World Beat Connection</a>

              by

        <a href="/profiles/dj-charlie" class="text-capitalize">
          DJ Charlieeeeeeeeeeeeeeeeeeeeeeeeeeeee        </a>
          </span>

    <span class="song-artist">
      <a href="<?php print $schedule_item['url']; ?>"
         class="text-capitalize"
         data-bind="title-link">
        <?php print $schedule_item['title']; ?>
      </a>

      <?php if ($schedule_item['showhost']['name']): ?>
        with

        <a href="<?php print $schedule_item['showhost']['url']; ?>"
           class="text-capitalize">
          <?php print $schedule_item['showhost']['name']; ?>
        </a>
      <?php //endif; ?>
    </span>
  <?php endif; ?>
</p>
