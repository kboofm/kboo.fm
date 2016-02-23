<?php
$stream = 'Stream 1';
$component = new ScheduleComponent();
$schedule_item = $component->now($stream);

$schedule = [
  'data' => [$schedule_item],
  'timestamp' => $schedule_item['start']['timestamp'],
  'type' => 'on-air',
  'stream' => $stream,
];

$schedule_url = NULL;
if (isset($schedule_item['url'])):
  $schedule_url = $schedule_item['url'];
endif;
?>


<p class="on-air margin-bottom-lg"
   data-stream="<?php print $schedule['stream']; ?>"
   data-type="<?php print $schedule['type']; ?>">

  <span class="">
    On Air:
  </span>
  
  <span class="song-artist">
    <a href="<?php print $schedule_url; ?>"
       class="text-capitalize"
       data-bind="title-link">
      <?php print $schedule_item['title']; ?>
    </a>

    <?php if ($schedule_item['showhost']['name']): ?>
      by

      <a href="<?php print $schedule_item['showhost']['url']; ?>"
         class="text-capitalize">
        <?php print $schedule_item['showhost']['name']; ?>
      </a>
    <?php endif; ?>
  </span>
</p>
