<?php
/**
 * @file
 * content_type_scheduled_timeslot.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_scheduled_timeslot_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function content_type_scheduled_timeslot_node_info() {
  $items = array(
    'scheduled_timeslot' => array(
      'name' => t('Scheduled Timeslot'),
      'base' => 'node_content',
      'description' => t('Timeslots for station schedule'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
