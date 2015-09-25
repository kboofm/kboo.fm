<?php
/**
 * @file
 * content_type_organization.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_organization_ctools_plugin_api($module = NULL, $api = NULL) {
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
function content_type_organization_node_info() {
  $items = array(
    'organization' => array(
      'name' => t('Organization or Place'),
      'base' => 'node_content',
      'description' => t('An organization or place. For example, a music venue, nonprofit organization, social aid & pleasure club, or business.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
