<?php


class NodeTeaserProcessor extends TemplateProcessor {

  public static function preprocess(&$vars) {
    if ($vars["view_mode"] != "teaser") {
      return;
    }

    $node = $vars['node'];
    $entity = entity_metadata_wrapper('node', $node);
    $image = NodeTeaserProcessor::getTeaserImage($entity);
    if ($image) {
      $image = NodeTeaserProcessor::getSizedImage($image, "teaser_150w");
    }

    try {
      $related_programs = $entity->field_related_programs->value();
      $related_programs = array_map(
        function ($item) {
          return [
            'title' => $item->title,
            'url' => NodeTeaserProcessor::getEntityUrl($item),
          ];
        },
        $related_programs
      );
    } catch (EntityMetadataWrapperException $e) {
      $related_programs = [];
    }

    try {
      $air_time = $entity->field_air_time->value();
      $starttime = $air_time['value'];
      $endtime = $air_time['value2'];

      $ymd_format = 'Y-m-d';
      $start_day = Helpers::toCarbonString($ymd_format, $starttime);
      $end_day = Helpers::toCarbonString($ymd_format, $endtime);
      $ends_different_day = ($start_day != $end_day);
    } catch (EntityMetadataWrapperException $e) {
      $starttime = "";
      $endtime = "";
      $ends_different_day = false;
    }

    $node_teaser = [
      'title' => NodeTeaserProcessor::getTeaserTitle($entity),
      'summary' => NodeTeaserProcessor::getTeaserSummary($entity),
      'related_programs' => $related_programs,
      'starttime' => $starttime,
      'endtime' => $endtime,
      'image' => $image,
      'ends_different_day' => $ends_different_day,
    ];

    $vars['node_teaser'] = $node_teaser;
    $vars['theme_hook_suggestions'][] = "node__teaser";

    NodeTeaserProcessor::preprocessPromo($vars, $node);
  }


  private static function preprocessPromo(&$vars, $node) {
    if ($node->type != "promo") {
      return;
    }

    $url = NodeTeaserProcessor::getEntityUrl($node);
    $vars['node_url'] = $url;
  }
}
