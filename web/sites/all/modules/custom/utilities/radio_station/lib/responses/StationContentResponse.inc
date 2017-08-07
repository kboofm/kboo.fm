<?php

class StationContentResponse extends Response {

  public function getAudio() {
    $this->template_name = 'radio_template_audio';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $component = new StationContentComponent();
    $pager = $component->getAudio($page, FALSE);

    $data = [
      'pager' => $pager,
      'nested_audio' => TRUE,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getAudioFeed() {
    $component = new StationContentComponent();
    $nids = $component->getAudioFeed();

	$processor = new PodcastProcessor();
	$rss = $processor->process($nids);
    $this->template_name = 'radio_template_programs_podcast';
    $this->addTemplateData($rss);
    $this->renderRss();
#    node_feed($nids);
  }


  public function getPodcast($alias, $type) {
    $content_types = array_keys(
      node_type_get_types()
    );

    if (in_array($type, $content_types)) {
      $entity = Response::getEntityFromAlias(
        $alias,
        $type
      );

      if (!$entity) {
        return MENU_NOT_FOUND;
      }

      $target = $entity->getIdentifier();
      $title = TemplateProcessor::getTeaserTitle($entity);
    } else {
      // Expect path for taxonomy term podcast
      // Url formatted as: vocabulary/term/podcast
      // Strip off the 3rd term (podcast) from the url
      // The remaining url can be used to access the taxonomy term
      $path = current_path();
      $path = explode("/", $path);
      array_pop($path);
      $path = implode("/", $path);
      $normal = drupal_get_normal_path($path);
      $parts = explode("/", $normal);

      $has_count = count($parts) == 3;
      $is_taxonomy = $parts[0] == "taxonomy";
      $is_term = $parts[1] == "term";

      if (!$has_count || !$is_taxonomy || !$is_term) {
        return MENU_NOT_FOUND;
      }

      $tid = $parts[2];
      $term = taxonomy_term_load($tid);

      if (!$term) {
        return MENU_NOT_FOUND;
      }

      $target = $tid;
      $title = $term->name;
    }

    $component = new StationContentComponent();
    $response = $component->getPodcast($target, $type);

    if ($type == "program") {
      $this->template_name = 'radio_template_programs_podcast';
      $this->addTemplateData($response);
      $this->renderRss();
    } else {
      $channel = [
        'title' => "{$title} Podcast",
      ];
      node_feed($response, $channel);
    }
  }
}
