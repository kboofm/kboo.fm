<?php

class ProgramProcessor extends TemplateProcessor {

  public function processGenres($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      try {
        $genres = $entity->field_genres->value();
      } catch (EntityMetadataWrapperException $e) {
        $genres = [];
      }

      $genres = array_map(
        function ($item) {
          return $item->name;
        },
        $genres
      );

      $unwrapped = $entity->value();
      $nodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'genres' => $genres,
      ];
    }

    return $nodes;
  }


  public function processTopics($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      try {
        $topics = $entity->field_topic_tags->value();
      } catch (EntityMetadataWrapperException $e) {
        $topics = [];
      }

      $topics = array_map(
        function ($item) {
          return $item->name;
        },
        $topics
      );

      $unwrapped = $entity->value();
      $nodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'topics' => $topics,
      ];
    }

    return $nodes;
  }
}
