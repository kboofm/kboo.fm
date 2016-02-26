<?php

class StationContentProcessor extends TemplateProcessor {
  public function process($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      $program = "";
      try {
        $programs = $entity->field_produced_for->value();

        if ($programs) {
          $program = $programs[0]->title;
        }
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }

      $unwrapped = $entity->value();
      $nodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'program' => $program,
      ];
    }

    return $nodes;
  }
}
