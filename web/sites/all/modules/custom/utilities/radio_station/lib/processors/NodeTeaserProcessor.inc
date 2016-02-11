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

    $published_date = NodeTeaserProcessor::getPublishedDate(
      $entity,
      "D, m/d/y"
    );

    $author = user_load($node->uid);
    $author_url = NodeTeaserProcessor::getEntityUrl($author, 'user');

    $node_teaser = [
      'title' => NodeTeaserProcessor::getTeaserTitle($entity),
      'author' => $author->name,
      'author_url' => $author_url,
      'published_date' => $published_date,
      'image' => $image,
      'summary' => NodeTeaserProcessor::getTeaserSummary($entity),
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
