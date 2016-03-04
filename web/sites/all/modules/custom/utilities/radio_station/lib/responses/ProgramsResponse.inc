<?php

class ProgramsResponse extends Response {

  public function getContent($program_alias) {
    $entity = Response::getEntityFromAlias(
      $program_alias,
      "program"
    );

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


  public function getPodcast($program_alias) {
    $entity = Response::getEntityFromAlias(
      $program_alias,
      "program"
    );

    if (!$entity) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_program_podcast';
    $program_nid = $entity->getIdentifier();
    $component = new StationContentComponent();
    $nids = $component->getPodcastForProgram($program_nid);
    node_feed($nids);
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
