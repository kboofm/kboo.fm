<?php

class RadioCache {

  public function clearSchedule($node) {
    $stream = EStreams::One;
    $timestamps = [];
    $entity = entity_metadata_wrapper('node', $node);

    if ($node->type == 'scheduled_timeslot') {
      try {
        $timestamps = $entity->field_timeslot->value();
      } catch (EntityMetadataWrapperException $e) {
        return;
      }

      try {
        $stream = $entity->field_stream->value();
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }

    } elseif ($node->type == 'station_content') {
      try {
        $timestamp = $entity->field_air_time->value();
        $timestamps = [$timestamp];
      } catch (EntityMetadataWrapperException $e) {
        return;
      }

      $programs = $entity->field_produced_for->value();
      $program = array_pop($programs);

      if (!$program) {
        return;
      }

      $program_entity = entity_metadata_wrapper('node', $program);

      try {
        $stream = $program_entity->field_stream->value();
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }
    }

    $cache_key_prefix = "radio_station_week_{$stream}_";
    $cache_table = "cache_radio_station_schedule";

    foreach ($timestamps as $timestamp) {
      $weekBegin = Helpers::weekBegin($timestamp['value']);
      $cache_key = "{$cache_key_prefix}{$weekBegin}";
      cache_clear_all($cache_key, $cache_table);
    }
  }
}
