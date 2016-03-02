<?php
/**
 * @file
 * content_type_station_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_station_content_ctools_plugin_api($module = NULL, $api = NULL) {
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
function content_type_station_content_node_info() {
  $items = array(
    'station_content' => array(
      'name' => t('Program Episode or Audio'),
      'base' => 'node_content',
      'description' => t('A show, episode, or an edition of a program. For example, an audio episode.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
