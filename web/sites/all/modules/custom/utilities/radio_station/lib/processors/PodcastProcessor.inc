<?php

class PodcastProcessor extends TemplateProcessor {

  private function processProgram($episode_entity) {
    try {
      $programs = $episode_entity->field_produced_for->value();
      $program = $programs[0];
    } catch (EntityMetadataWrapperException $e) {
      return null;
    }

    $entity = entity_metadata_wrapper('node', $program);
    $program_url = $this->getEntityUrl($program, 'node', true);
    $image = $this->getTeaserImage($entity);

    if ($image) {
      $image = $this->getSizedImage($image, "teaser_150w", true);
    }

    $description = $entity->body->value();
    $description = $description['value'];
    $description = drupal_html_to_text($description);

    $program_data = [
      'title' => $this->getTeaserTitle($entity),
      'image' => $image,
      'url' => $program_url,
      'podcast_url' => "{$program_url}/podcast",
      'subtitle' => $entity->field_short_description->value(),
      'summary' => $this->getTeaserSummary($entity),
      'description' => $description,
      'itunes_parent_category' => $entity->field_itunes_parent_category->value(),
      'itunes_child_category' => $entity->field_itunes_child_category->value(),
      'explicit' => $entity->field_explicit->value(),
    ];

    return $program_data;
  }


  public function process($nids) {
    $program = null;
    $items = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      if (!$program) {
        $program = $this->processProgram($entity);
      }

      $image = $this->getTeaserImage($entity);
      if ($image) {
        $image = $this->getSizedImage($image, "teaser_150w", true);
      }

      $published_date = NodeTeaserProcessor::getPublishedDate(
        $entity,
        "D, d M Y H:i:s O"
      );

      $audio_file = null;
      try {
        $audio_files = $entity->field_audio_files->value();
      } catch (EntityMetadataWrapperException $e) {
        // duck typing
      }

      if (isset($audio_files[0])) {
        $audio = $audio_files[0];
        $audio_file = file_create_url($audio['uri']);
      }

      $description = $entity->body->value();
      $description = $description['value'];
      $description = drupal_html_to_text($description);

      $unwrapped = $entity->value();
      $entity_url = $this->getEntityUrl($unwrapped, 'node', true);

      $items[] = [
        'url' => $entity_url,
        'title' => $this->getTeaserTitle($entity),
        'image' => $image,
        'published_date' => $published_date,
        'audio_file' => $audio_file,
        'duration' => $audio['filesize'],
        'subtitle' => $entity->field_short_description->value(),
        'summary' => $this->getTeaserSummary($entity),
        'description' => $description,
      ];
    }

    return [
      'program' => $program,
      'items' => $items,
    ];
  }
}
