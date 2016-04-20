<?php

class ScheduleCache extends BaseCache {

  public function __construct() {
    parent::__construct();
    $this->table = "cache_radio_station_schedule";
    $this->keyPrefix = "radio_station_week_";
  }


  public function clear($node) {
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

    foreach ($timestamps as $timestamp) {
      $weekBegin = Helpers::weekBegin($timestamp['value']);
      $this->forceClear("{$stream}_{$weekBegin}");
    }
  }
}
