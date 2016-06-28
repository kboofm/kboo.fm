<?php

class ProfilesResponse extends Response {
  public function getContributors() {
    $this->template_name = 'radio_template_about_contributors';
    $component = new ProfilesComponent();
    $profiles = $component->getContributors();

    $data = [
      'profiles' => $profiles,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getPodcast($profile_alias) {
    $entity = Response::getEntityFromAlias(
      $profile_alias,
      "person_profile"
    );

    if (!$entity) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_profiles_podcast';
    $profile_nid = $entity->getIdentifier();
    $component = new StationContentComponent();
    $nids = $component->getPodcastForProfile($profile_nid);
    node_feed($nids);
  }

  public function getShowHosts() {
    $this->template_name = 'radio_template_programs_show_hosts';
    $this->readParams();
    $title = $this->getParam('title', null);
    $status = $this->getParam('status', EShowHostStatus::Active);

    if ($status == EShowHostStatus::Both) {
      $status = null;
    }

    $component = new ProfilesComponent();
    $profiles = $component->getShowHosts($title, $status);
    $alpha_pager = RadioPaginator::alphabetic($profiles);

    $data = [
      'profiles' => $profiles,
      'alpha_pager' => $alpha_pager,
      'form' => [
        'title' => $title,
        'status' => $status,
      ],
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
