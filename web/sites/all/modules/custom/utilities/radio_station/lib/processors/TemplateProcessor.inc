<?php

class TemplateProcessor {

  public static function getTeaserTitle($entity) {
    $title = $entity->title->value();

    try {
      $teaser_title = $entity->field_teaser_title->value();
      if (!empty($teaser_title)) {
        $title = $teaser_title;
      }
    } catch (EntityMetadataWrapperException $e) {
      // duck typing
    }

    return $title;
  }


  public static function getTeaserImage($entity) {
    $image = null;

    try {
      $image = $entity->field_more_images[0]->file->value();
    } catch (EntityMetadataWrapperException $e) {
      // ducktyping
    }

    try {
      $image_gallery = $entity->field_image_gallery[0];
      $image = $image_gallery->field_image_files[0]->file->value();
    } catch (EntityMetadataWrapperException $e) {
      // ducktyping
    }

    try {
      $image = $entity->field_lead_image->file->value();
    } catch (EntityMetadataWrapperException $e) {
      // ducktyping
    }

    try {
      $image = $entity->field_teaser_image->file->value();
    } catch (EntityMetadataWrapperException $e) {
      // ducktyping
    }

    return $image;
  }


  public static function getTeaserSummary($entity) {
    $summary = null;

    try {
      $summary = $entity->field_teaser_summary->value();
    } catch (EntityMetadataWrapperException $e) {
      // duck typing
    }

    if (!$summary) {
      $body = $entity->body->value();
      $summary = $body['value'];
      $summary = drupal_html_to_text($summary);
    }

    return mb_strimwidth($summary, 0, 280, "...");
  }


  public static function getEntityUrl(
    $object,
    $type = 'node',
    $absolute = false
  ) {

    if (is_null($object)) {
      return NULL;
    }

    if ($object->type == 'promo') {
      $wrapped = entity_metadata_wrapper($type, $object);
      $link = $wrapped->field_link->value();

      if ($link) {
        $url = $link['url'];

        if (!Helpers::hasProtocol($url)) {
          $protocol = Helpers::getProtocol();
          $url = "{$protocol}{$url}";
        }

        return $url;
      }
    }

    $uri = entity_uri($type, $object);
    $uri['options']['absolute'] = $absolute;

    return url(
      $uri['path'],
      $uri['options']
    );
  }


  public static function getSizedImage(
    $image,
    $style = 'default_lead_1x',
    $absolute = false
) {
    $styled_uri = image_style_url($style, $image->uri);

    if (!file_exists($styled_uri)) {
      image_style_create_derivative(
        image_style_load($style),
        $image->uri,
        $styled_uri
      );
    }

    file_create_url($styled_uri);

    if ($absolute) {
      return $styled_uri;
    }

    return parse_url(
      $styled_uri,
      PHP_URL_PATH
    );
  }


  public static function getPublishedDate($entity, $format) {
    try {
      $published_date = $entity->published_at->value();
      $published_date = Helpers::toCarbonString($format, $published_date);
    } catch (EntityMetadataWrapperException $e) {
      $published_date = null;
    }

    return $published_date;
  }
}