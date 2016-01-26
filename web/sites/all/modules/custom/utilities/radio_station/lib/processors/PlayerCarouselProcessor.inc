<?php

class PlayerCarouselProcessor extends TemplateProcessor {
  public function process($dataset) {
    $promos = [];

    foreach ($dataset as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $image = $this->getTeaserImage($entity);

      $alt = NULL;
      if (isset($image->field_file_image_alt_text['und'][0]['value'])) {
        $alt = $image->field_file_image_alt_text['und'][0]['value'];
      }

      $thumbnail = $this->getSizedImage(
        $image,
        'thumbnail'
      );

      $unwrapped = $entity->value();
      $promos[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'image' => $thumbnail,
        'alt' => $alt,
        'title' => $this->getTeaserTitle($entity),
      ];
    }

    return $promos;
  }
}
