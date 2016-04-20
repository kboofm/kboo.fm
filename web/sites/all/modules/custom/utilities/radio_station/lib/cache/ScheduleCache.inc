<?php

class ScheduleCache extends BaseCache {

  public function __construct() {
    parent::__construct();
    $this->table = "cache_radio_station_schedule";
    $this->keyPrefix = "radio_station_week_";
  }


  public function clear($node) {
    switch ($node->type) {
      case "scheduled_timeslot":
        $this->clearScheduledTimeslot($node);
        break;
      case "station_content":
        $this->clearStationContent($node);
        break;
    }
  }


  public function clearWeeks(
    $min,
    $max,
    $allowThisWeek = true,
    $stream = EStreams::One
  ) {

    $now = time();
    $rover = Helpers::carbonize($now);
    $rover->subWeeks($min);
    for ($i = $min; $i <= $max; $i++) {
      if ($i == 0 && !$allowThisWeek) {
        continue;
      }

      $timestamp = $rover->getTimestamp();
      $weekBegin = Helpers::weekBegin($timestamp);
      $this->forceClear("{$stream}_{$weekBegin}");
    }
  }


  private function clearScheduledTimeslot($node) {
    $stream = EStreams::One;
    $entity = entity_metadata_wrapper('node', $node);

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

    foreach ($timestamps as $timestamp) {
      $weekBegin = Helpers::weekBegin($timestamp['value']);
      $this->forceClear("{$stream}_{$weekBegin}");
    }
  }


  private function clearStationContent($node) {
    $stream = EStreams::One;
    $entity = entity_metadata_wrapper('node', $node);

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

    foreach ($timestamps as $timestamp) {
      $weekBegin = Helpers::weekBegin($timestamp['value']);
      $this->forceClear("{$stream}_{$weekBegin}");
    }
  }
}
