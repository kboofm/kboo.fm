<?php

/**
 * @file
 * Drush integration for the Pathauto module.
 */

/**
 * Implements hook_drush_command().
 */
function pathauto_drush_command() {
  $items['pathauto-aliases-generate'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
    'drupal_dependencies' => array('pathauto'),
    'description' => 'Generate aliases for all unaliased entities of a specific type, or all possible entities.',
    'arguments' => array(
      'type' => 'The particular entity type to process. Omit this argument to choose from available entity types.',
    ),
    'callback' => 'drush_pathauto_aliases_generate',
    'aliases' => array('pag'),
  );

  $items['pathauto-aliases-delete'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
    'drupal_dependencies' => array('pathauto'),
    'description' => 'Delete aliases for all aliased entities of a specific type, or all possible entities.',
    'arguments' => array(
      'type' => 'The particular entity type to process. Omit this argument to choose from available entity types.',
    ),
    'callback' => 'drush_pathauto_aliases_delete',
    'aliases' => array('pad'),
  );

  return $items;
}

/**
 * Command callback for drush pathauto-aliases-generate.
 */
function drush_pathauto_aliases_generate($type = NULL) {
  $types = _drush_pathauto_aliases_get_batch_types();

  // Check if the provided type ($type) is a valid bulk generate type.
  if ($type) {
    if ($type != 'all' && !isset($types[$type])) {
      return drush_set_error(dt("'!type' entity type is not a valid entity type for bulk generation", array('!type' => $type)));
    }
  }
  else {
    $type = drush_choice(array('all' => 'all') + $types, 'Enter a number to choose which entity types to bulk generate aliases.', '!key');
  }
  
  if ($type !== FALSE) {
    foreach (module_invoke_all('pathauto', 'settings') as $settings) {
      // Get settings for each batch update callback
      if (!empty($settings->batch_update_callback)) {
        $form['#update_callbacks'][$settings->batch_update_callback] = $settings;
      }
    }

    // Set up the batch using the bulk generate form submission handler.
    module_load_include('inc', 'pathauto', 'pathauto.admin');
    $form_state = array();
    if ($type == 'all') {
      $form_state['values']['update'] = $types;
    }
    else {
      $form_state['values']['update'][] = $types[$type];
    }

    pathauto_bulk_update_form_submit($form, $form_state);
    $batch =& batch_get();
    $batch['progressive'] = FALSE;

    // Process the batch.
    drush_backend_batch_process();
  }
}

/**
 * Command callback for drush pathauto-aliases-delete.
 */
function drush_pathauto_aliases_delete($type = NULL) {
  $types = _drush_pathauto_aliases_get_entity_types();

  // Check if the provided type ($type) is a valid bulk generate type.
  if ($type) {
    if ($type != 'all' && !isset($types[$type])) {
      return drush_set_error(dt("'!type' entity type is not a valid entity type for bulk deletion", array('!type' => $type)));
    }
  }
  else {
    $type = drush_choice(array('all' => 'all') + $types, 'Enter a number to choose which entity types to bulk delete aliases.', '!key');
  }

  if ($type !== FALSE) {
    // Set up the batch using the bulk generate form submission handler.
    module_load_include('inc', 'pathauto', 'pathauto.admin');
    $form_state = array();
    if ($type == 'all') {
      $form_state['values']['all_aliases'] = TRUE;
    }
    else {
      $form_state['values'][$types[$type]] = TRUE;
    }
    pathauto_admin_delete_submit($form, $form_state);
  }
}

/**
 * Get batch function callbacks.
 */
function _drush_pathauto_aliases_get_batch_types() {
  $types = array();
  foreach (module_invoke_all('pathauto', 'settings') as $settings) {
    if (!empty($settings->batch_update_callback)) { 
      $types[$settings->module] = $settings->batch_update_callback;
    }
  }
  return $types;
}
  
/**
* Get entity types for aliases.
*/
function _drush_pathauto_aliases_get_entity_types() {
  $objects = module_invoke_all('path_alias_types');
  $types = array();
  foreach ($objects as $key => $value) {
    $types["$value"] = $key;
  }
  return $types;
}