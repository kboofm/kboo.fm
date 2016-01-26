<?php


class EventsProcessor extends TemplateProcessor {
  public function processTable($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $acts = [];
      $timestamp = null;

      $entity = entity_metadata_wrapper('node', $nid);
      $unwrapped = $entity->value();

      $list = $entity->field_event_date->value();
      foreach ($list as $entry) {
        $timestamp = $entry['value'];
        break;
      }

      $list = $entity->field_related_acts->value();
      foreach ($list as $act) {
        $acts[] = [
          'title' => $act->title,
          'url' => $this->getEntityUrl($act),
        ];
      }

      $unwrapped_venue = $entity->field_venue->value();
      if ($unwrapped_venue) {
        $venue_entity = entity_metadata_wrapper('node', $unwrapped_venue);
        $venue = [
          'title' => $this->getTeaserTitle($venue_entity),
          'url' => $this->getEntityUrl($unwrapped_venue),
        ];
      }

      $nodes[] = [
        'nid' => $entity->getIdentifier(),
        'title' => $entity->title->value(),
        'event_date' => $timestamp,
        'url' => $this->getEntityUrl($unwrapped),
        'venue' => $venue,
        'acts' => $acts,
      ];
    }

    return $nodes;
  }


  public function processGeneratedScript($nids) {
    $venues = [];
    $timestamp = null;

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);
      $list = $entity->field_event_date->value();

      foreach ($list as $entry) {
        $timestamp = $entry['value'];
        break;
      }

      $notes = $entity->field_livewire_notes->value();
      $unwrapped_venue = $entity->field_venue->value();

      if (!$unwrapped_venue) {
        continue;
      }

      $venue = entity_metadata_wrapper('node', $unwrapped_venue);
      $venue_nid = $venue->getIdentifier();

      if (!isset($venues[$venue_nid])) {
        $venues[$venue_nid] = [
          'title' => $this->getTeaserTitle($venue),
          'url' => $this->getEntityUrl($unwrapped_venue),
          'events' => [],
        ];
      }

      $unwrapped = $entity->value();
      $venues[$venue_nid]['events'][] = [
        'nid' => $entity->getIdentifier(),
        'starttime' => $timestamp,
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'notes' => $notes,
      ];
    }

    usort(
      $venues,
      function ($a, $b) {
        $left = strtolower($a['title']);
        $right = strtolower($b['title']);
        return strnatcmp($left, $right);
      }
    );

    return $venues;
  }


  public function processLivewireScript($dataset) {
    $events = [];
    $timestamp = null;

    foreach ($dataset as $nid => $dummy) {
      $entity = entity_metadata_wrapper('node', $nid);
      $list = $entity->field_event_date->value();

      foreach ($list as $entry) {
        $timestamp = $entry['value'];
        break;
      }

      $override = $entity->field_livewire_override->value();
      if ($override == ELivewireOverride::DontInclude) {
        continue;
      }

      $always_include = ($override == ELivewireOverride::AlwaysInclude);
      $notes = $entity->field_livewire_notes->value();
      $venue = $entity->field_venue->value();

      if (!$venue) {
        continue;
      }

      $venue = entity_metadata_wrapper('node', $venue);
      $venue_rating = $venue->field_livewire_rating->value();

      $events[] = [
        'nid' => $entity->getIdentifier(),
        'time' => Helpers::toCarbonString('g:i', $timestamp),
        'timestamp' => $timestamp,
        'title' => $this->getTeaserTitle($entity),
        'venue' => $this->getTeaserTitle($venue),
        'rating' => $venue_rating,
        'always_include' => $always_include,
        'notes' => $notes,
      ];
    }

    usort(
      $events,
      function ($a, $b) {
        $left = strtolower($a['venue']);
        $right = strtolower($b['venue']);
        $comparison = strnatcmp($left, $right);

        if ($comparison == 0) {
          $left = strtolower($a['timestamp']);
          $right = strtolower($b['timestamp']);
          $comparison = strnatcmp($left, $right);
        }

        return $comparison;
      }
    );

    return $events;
  }


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
