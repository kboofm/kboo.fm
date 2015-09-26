<?php
/**
 * @file
 * content_type_standalone_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_standalone_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function content_type_standalone_media_node_info() {
  $items = array(
    'standalone_media' => array(
      'name' => t('Standalone Media'),
      'base' => 'node_content',
      'description' => t('A show, episode, release, or an edition of a program. For example, an audio episode or an edition of a newsletter.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
