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

  public function getHostContent($host_profile) {
    $node = node_load($host_profile);
    $entity = entity_metadata_wrapper('node', $node);

    if (!$entity) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_program_content';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $hp_id = $entity->getIdentifier();
    $component = new StationContentComponent();
    $pager = $component->getContentForHost($hp_id, $page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getCurrentShows() {
    $this->template_name = 'radio_template_program';

    return $this->getShows(
      EProgramStatus::Current,
      EStreams::One
    );
  }


  public function getRetiredShows() {
    $this->template_name = 'radio_template_program_retired';

    return $this->getShows(
      EProgramStatus::Retired,
      EStreams::all()
    );
  }


  public function getWebOnlyShows() {
    $this->template_name = 'radio_template_program_web_only';

    return $this->getShows(
      EProgramStatus::Current,
      EStreams::Two
    );
  }


  private function getShows($status, $streams) {
    $component = new ProgramsComponent();
    $programs = $component->getShows($status, $streams);

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
