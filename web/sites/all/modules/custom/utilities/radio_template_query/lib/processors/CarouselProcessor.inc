<?php

class CarouselProcessor extends TemplateProcessor {
  public function process($dataset, $heading = NULL) {
    $promos = [];

    foreach ($dataset as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $lead_image = $entity->field_lead_image->file->value();

      $alt = NULL;
      if (isset($lead_image->field_file_image_alt_text['und'][0]['value'])) {
        $alt = $lead_image->field_file_image_alt_text['und'][0]['value'];
      }

      $lead_image_url = $this->getSizedImage(
        $lead_image,
        'default_gallery_large_2x'
      );

      $unwrapped = $entity->value();
      $promos[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'image' => $lead_image_url,
        'alt' => $alt,
        'title' => $entity->title->value(),
      ];
    }

    return $promos;
  }
}
