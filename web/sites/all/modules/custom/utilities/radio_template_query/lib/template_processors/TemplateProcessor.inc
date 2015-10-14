<?php

class TemplateProcessor {
  public function process($dataset) {}

  public static function getEntityUrl($entity, $type = 'node') {
    if (is_null($entity)) {
      return NULL;
    }

    $uri = entity_uri($type, $entity);
    return url($uri['path'], $uri['options']);
  }


  public static function getSizedImage($image, $style = 'default_lead_1x') {
    $styled_uri = image_style_url($style, $image->uri);

    if (!file_exists($styled_uri)) {
      image_style_create_derivative(
        image_style_load($style),
        $image->uri, $styled_uri
      );
    }

    file_create_url($styled_uri);
    return parse_url($styled_uri, PHP_URL_PATH);
  }
}