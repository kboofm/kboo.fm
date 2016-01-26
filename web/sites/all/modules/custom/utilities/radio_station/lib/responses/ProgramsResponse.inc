<?php

class ProgramsResponse extends Response {
  private static function getEntity($program_alias) {
    $url_alias = "programs/{$program_alias}";

    $path = drupal_lookup_path("source", $url_alias);
    if (!$path) {
      return MENU_NOT_FOUND;
    }

    $node = menu_get_object("node", 1, $path);
    if (!$node) {
      return MENU_NOT_FOUND;
    }

    if ($node->type != 'program') {
      return MENU_NOT_FOUND;
    }

    $entity = entity_metadata_wrapper('node', $node);

    $program_type = $entity->field_program_type->value();
    if (!$program_type || $program_type->name != 'Show') {
      return MENU_NOT_FOUND;
    }

    return $entity;
  }


  public static function getTitle($program_alias) {
    $entity = ProgramsResponse::getEntity($program_alias);
    return $entity->title->value();
  }


  public function getContent($program_alias) {
    $entity = ProgramsResponse::getEntity($program_alias);
    if ($entity == MENU_NOT_FOUND) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_programs_content';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $program_nid = $entity->getIdentifier();
    $component = new StationContentComponent();
    $pager = $component->getContentForProgram($program_nid, $page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
