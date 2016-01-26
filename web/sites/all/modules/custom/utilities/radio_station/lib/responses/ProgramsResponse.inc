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


  public function getPodcast($program_alias) {
    $entity = ProgramsResponse::getEntity($program_alias);
    if ($entity == MENU_NOT_FOUND) {
      return MENU_NOT_FOUND;
    }

    $this->template_name = 'radio_template_programs_podcast';
    $program_nid = $entity->getIdentifier();
    $component = new StationContentComponent();
    $data = $component->getPodcastForProgram($program_nid);

    $this->addTemplateData($data);
    return $this->renderRss();
  }


  public function getStreams() {
    $this->template_name = 'radio_template_programs_streams';

    $icon_path = drupal_get_path('theme', 'wwozui');
    $icon_path = "/{$icon_path}/images/stream-icons";

    $data = [
      'icon_path' => $icon_path,
      'devices' => [
        'itunes' => [
          'title' => "iPhone",
          'url' => "http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=325390384&amp;mt=8&amp;uo=6",
          'icon' => "{$icon_path}/iPhone-gray.png",
          'qr_image' => "{$icon_path}/iphone-qr.png",
        ],
        'android' => [
          'title' => "Android",
          'url' => "http://market.android.com/details?id=org.wwoz",
          'icon' => "{$icon_path}/Android-gray.png",
          'qr_image' => "{$icon_path}/android-qr.png",
        ],
        'blackberry' => [
          'title' => "Blackberry",
          'url' => "https://appworld.blackberry.com/webstore/content/18633",
          'icon' => "{$icon_path}/Blackberry-gray.png",
          'qr_image' => "{$icon_path}/blackberry-qr.png",
        ],
      ],
    ];

    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
