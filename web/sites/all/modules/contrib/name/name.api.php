<?php
/**
 * @file
 * API documentation for the Name field module.
 */

/**
 * Defines available name field autocomplete sources.
 *
 * @return array
 *   An array of autocomplete sources. Each source is an associative array
 *   that may contain the following key-value pairs:
 *   - "name": Required. The label for the autocomplete source.
 *   - "autocomplete callback": Optional. The function that does the query.
 *   - "autocomplete arguments": Optional. Additional arguments to pass to
 *     the callback function.
 *   - "list callback": Optional. Returns a full data listing.
 *   - "list arguments": Optional. Additional arguments to pass to
 *     the callback function.
 *   - "components": Optional. Limit the components are allowed this source.
 *   - "autonomous": Optional. Determines if this can be run outside of the
 *     field API. Defaults to FALSE.
 *
 * @see name_field_autocomplete_query()
 */
function hook_name_data_sources() {
  return array(
    'title' => array(
      'name' => t('Title options'),
      'components' => array('title'),
      'autocomplete callback' => 'name_field_autocomplete_query',
      'autocomplete arguments' => array('title'),
      'list callback' => 'name_field_get_options',
      'list arguments' => array(),
    ),
    'data' => array(
      'name' => t('Existing content'),
      'autonomous' => TRUE,
      'autocomplete callback' => 'name_field_data_query',
    ),
  );
}

/**
 * Allows other modules to react to hook_field_insert().
 *
 * Triggers a custom hook for name field inserts. Field API only calls the
 * module that defines the field.
 *
 * @see hook_field_insert().
 */
function hook_name_field_insert_notification($entity_type, $entity, $field, $instance, $langcode, &$items) {
}

/**
 * Allows other modules to react to hook_field_update().
 *
 * Triggers a custom hook for name field updates. Field API only calls the
 * module that defines the field.
 *
 * @see hook_field_update().
 */
function hook_name_field_update_notification($entity_type, $entity, $field, $instance, $langcode, &$items) {
}
