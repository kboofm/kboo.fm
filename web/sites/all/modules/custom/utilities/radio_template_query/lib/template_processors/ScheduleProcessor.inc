<?php

class ScheduleProcessor extends TemplateProcessor {
  public function process($dataset) {
    $programs = [];

    foreach ($dataset as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $programs[] = $this->getProgram($entity);
    }

    return $programs;
  }

  public function processFirst($dataset) {
    reset($dataset);
    $nid = key($dataset);
    $entity = entity_metadata_wrapper('node', $nid);
    return $this->getProgram($entity);
  }

  private function getProgram($unwrapped_entity) {
    try {
      return $unwrapped_entity->field_program->value();
    } catch (EntityMetadataWrapperException $e) {
      return NULL;
    }
  }
}
