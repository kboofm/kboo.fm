<?php

class TeaserTileProcessor extends TemplateProcessor {
  public function process($dataset, $heading, $more_link) {
    $first = TRUE;
    $lead_title = NULL;
    $lead_url = NULL;
    $image_url = NULL;
    $list = [];

    foreach ($dataset as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $unwrapped = $entity->value();
      $url = $this->getEntityUrl($unwrapped);

      if ($first) {
        $first = FALSE;

        $image = $this->getTeaserImage($entity);
        if ($image) {
          $image_url = $this->getSizedImage($image);
        }

        $lead_url = $url;
        $lead_title = $this->getTeaserTitle($entity);
      } else {
        $list[] = [
          'icon' => TRUE,
          'title' => $this->getTeaserTitle($entity),
          'url' => $url,
        ];
      }
    }

    return
      [
        'url' => $lead_url,
        'type' => 'content',
        'heading' => $heading,
        'more_link' => $more_link,
        'image' => $image_url,
        'title' => [
          'icon' => TRUE,
          'text' => $lead_title,
        ],
        'list' => $list,
      ];
  }
}