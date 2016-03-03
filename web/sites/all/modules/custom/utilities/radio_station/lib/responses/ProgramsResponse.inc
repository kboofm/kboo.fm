<?php

class ProgramsResponse extends Response {
  private static function getEntity($program_alias) {
    $pattern = variable_get("pathauto_node_program_pattern", "program");
    $pattern = explode("/", $pattern);
    $pattern = reset($pattern);
    $url_alias = "{$pattern}/{$program_alias}";

    $path = drupal_lookup_path("source", $url_alias);
    if (!$path) {
      return null;
    }

    $node = menu_get_object("node", 1, $path);
    if (!$node) {
      return null;
    }

    if ($node->type != 'program') {
      return null;
    }

    return entity_metadata_wrapper('node', $node);
  }


  public static function getTitle($program_alias) {
    $entity = ProgramsResponse::getEntity($program_alias);
    $title = "";

    if ($entity) {
      $title = $entity->title->value();
    }

    return $title;
  }


  public function getContent($program_alias) {
    $entity = ProgramsResponse::getEntity($program_alias);
    if (!$entity) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_program_content';
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


  public function getShows() {
    $this->template_name = 'radio_template_program';

    $component = new ProgramsComponent();
    $programs = $component->getShows();

    $data = [
      'programs' => $programs,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getGenres() {
    $this->template_name = 'radio_template_program_genre';
    $component = new ProgramsComponent();
    $genres = $component->getGenres();

    $data = [
      'genres' => $genres,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getTopics() {
    $this->template_name = 'radio_template_program_topic';
    $component = new ProgramsComponent();
    $topics = $component->getTopics();

    $data = [
      'topics' => $topics,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
