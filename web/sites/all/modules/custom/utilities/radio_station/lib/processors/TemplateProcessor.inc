<?php

class TemplateProcessor {

  public static function getTeaserTitle($entity) {
    $title = $entity->title->value();
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
      $image = $entity->field_lead_image->file->value();
    } catch (EntityMetadataWrapperException $e) {
      // ducktyping
    }

    return $image;
  }


  public static function getTeaserSummary($entity) {
    $summary = null;

    if (!$summary) {
      $body = $entity->body->value();
      $summary = $body['value'];
      $summary = Helpers::htmlToText($summary);
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

    if (isset($object->type) && $object->type == 'promo') {
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


  public static function groupAlphabetically($data) {
    $alphabet = array_fill_keys(
      range('A', 'Z'),
      []
    );

    # This will hold all non-alphabetic titles
    $alphabet['#'] = [];

    foreach ($data as $item) {
      $first_letter = strtoupper($item['title'][0]);

      if (isset($alphabet[$first_letter])) {
        $alphabet[$first_letter][] = $item;
      } else {
        $alphabet['#'][] = $item;
      }
    }

    $alphabet = array_filter(
      $alphabet,
      function ($item) {
        return (count($item) > 0);
      }
    );

    return $alphabet;
  }


  public static function groupByKey($data, $key) {
    $set = [];

    foreach ($data as $item) {
      $values = $item[$key];

      if (!is_array($values)) {
        $values = [$values];
      }

      foreach ($values as $value) {
        if (!isset($set[$value])) {
          $set[$value] = [];
        }

        $set[$value][] = $item;
      }
    }

    return $set;
  }
}