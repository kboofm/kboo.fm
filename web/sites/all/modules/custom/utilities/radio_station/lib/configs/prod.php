<?php
return [
  'environment' => 'prod',
  'cron_generate_episodes' => TRUE,
  'cron_automatic_ripping' => TRUE,
  'cron_attach_rips' => TRUE,
  'cron_generate_cache_schedule_this_week' => TRUE,
  'cron_generate_cache_schedule_previous_weeks' => 1,
  'cron_generate_cache_schedule_next_weeks' => 4,
  'onsave_clear_cache_schedule' => TRUE,
  'onsave_clear_cache_sidebar' => TRUE,
];
