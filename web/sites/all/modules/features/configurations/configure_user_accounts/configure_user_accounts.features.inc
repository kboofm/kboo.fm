<?php
/**
 * @file
 * configure_user_accounts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function configure_user_accounts_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
