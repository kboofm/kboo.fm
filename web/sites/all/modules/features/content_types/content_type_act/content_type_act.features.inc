<?php
/**
 * @file
 * content_type_act.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_act_ctools_plugin_api($module = NULL, $api = NULL) {
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
function content_type_act_node_info() {
  $items = array(
    'act' => array(
      'name' => t('Act'),
      'base' => 'node_content',
      'description' => t('A musical act, group, or artist.'),
      'has_title' => '1',
      'title_label' => t('Act Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
