<?php

class ProgramProcessor extends TemplateProcessor {

  public function process($nids) {
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
}
