<?php
/**
 * @file
 * configure_admin_ui.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function configure_admin_ui_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
