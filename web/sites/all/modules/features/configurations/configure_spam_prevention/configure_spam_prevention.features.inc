<?php
/**
 * @file
 * configure_spam_prevention.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function configure_spam_prevention_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "captcha" && $api == "captcha") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
