<?php

class RadioCache {

  public function clearSidebar($node) {
    if ($node->type != "station_content") {
      return;
    }

    $cache_table = "cache_radio_station";
    cache_clear_all("radio_station_latest_playlists", $cache_table);

    $clear = false;
    $entity = entity_metadata_wrapper('node', $node);
    try {
      $audio_files = $entity->field_audio_files->value();
      if (count($audio_files) > 0) {
        $clear = true;
      }
    } catch (EntityMetadataWrapperException $e) {
      // duck typing
    }

    if ($clear) {
      cache_clear_all("radio_station_latest_audio", $cache_table);
    }
  }


  public function clearSchedule($node) {
    $stream = EStreams::One;
    $timestamps = [];
    $types = [
      'scheduled_timeslot',
      'station_content',
    ];

    if (!in_array($node->type, $types)) {
      return;
    }

    $entity = entity_metadata_wrapper('node', $node);
    if ($node->type == 'scheduled_timeslot') {
      try {
        $timestamps = $entity->field_timeslot->value();
      } catch (EntityMetadataWrapperException $e) {
        return;
      }

      try {
        $stream = $entity->field_stream->value();
        $stream = EStreams::getStreamByNid($stream->nid);
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }

    } elseif ($node->type == 'station_content') {
      try {
        $timestamp = $entity->field_air_time->value();
        if (!$timestamp) {
          return;
        }

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
