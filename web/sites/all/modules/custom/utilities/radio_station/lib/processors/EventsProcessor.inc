<?php


class EventsProcessor extends TemplateProcessor {

  public function process($dataset, $style) {
    switch ($style) {
      case EDisplayStyle::Small:
        return $this->processSmall($dataset);
      case EDisplayStyle::Medium:
        return $this->processMedium($dataset);
      default:
        return [];
    }
  }

  public function processSmall($dataset) {
    $events = [];
    $timestamp = null;

    foreach ($dataset as $nid => $dummy) {
      $entity = entity_metadata_wrapper('node', $nid);
      $list = $entity->field_event_date->value();

      foreach ($list as $entry) {
        $timestamp = $entry['value'];
        break;
      }

      $unwrapped_venue = $entity->field_venue->value();
      $venue_url = NULL;
      $venue_title = NULL;

      if ($unwrapped_venue) {
        $venue = entity_metadata_wrapper('node', $unwrapped_venue);
        $venue_url = $this->getEntityUrl($unwrapped_venue);
        $venue_title = $this->getTeaserTitle($venue);
      }

      $unwrapped = $entity->value();

      $event = [
        'url' => $this->getEntityUrl($unwrapped),
        'starttime' => $timestamp,
        'title' => $this->getTeaserTitle($entity),
        'venue' => $venue_title,
        'venue_url' => $venue_url,
      ];

      $events[] = $event;
    }

    return $events;
  }


  public function processMedium($dataset) {
    $events = [];

    foreach ($dataset as $nid => $dummy) {
      $entity = entity_metadata_wrapper('node', $nid);
      $list = $entity->field_event_date->value();

      foreach ($list as $entry) {
        $timestamp = $entry['value'];
        $endtime = $entry['value2'];
        break;
      }

      $unwrapped_venue = $entity->field_venue->value();
      if ($unwrapped_venue) {
        $venue = entity_metadata_wrapper('node', $unwrapped_venue);
        $venue_title = $this->getTeaserTitle($venue);
      } else {
        $location = $entity->field_location->value();
        $venue_title = $location['name_line'];
      }

      try {
        $image = $this->getTeaserImage($entity);
        $image = $this->getSizedImage(
          $image,
          'medium'
        );
      } catch (EntityMetadataWrapperException $e) {
        $image = '';
      }

      $ymd_format = 'Y-m-d';
      $start_day = Helpers::toCarbonString($ymd_format, $timestamp);
      $end_day = Helpers::toCarbonString($ymd_format, $endtime);
      $ends_different_day = ($start_day != $end_day);

      $unwrapped = $entity->value();
      $event = [
        'title' => $this->getTeaserTitle($entity),
        'url' => $this->getEntityUrl($unwrapped),
        'image' => $image,
        'starttime' => $timestamp,
        'endtime' => $endtime,
        'venue_location_name' => $venue_title,
        'ends_different_day' => $ends_different_day,
      ];

      $events[] = $event;
    }

    return $events;
  }
}
