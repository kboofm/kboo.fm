<?php
/**
 * @file
 * content_type_program.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_program_ctools_plugin_api($module = NULL, $api = NULL) {
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
function content_type_program_node_info() {
  $items = array(
    'program' => array(
      'name' => t('Program'),
      'base' => 'node_content',
      'description' => t('A KBOO Program, or initiative.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
