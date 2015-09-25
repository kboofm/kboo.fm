<?php
/**
 * @file
 * configure_text_editing.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function configure_text_editing_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "entity_embed" && $api == "default_entity_embed_configurations") {
    return array("version" => "1");
  }
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
}
