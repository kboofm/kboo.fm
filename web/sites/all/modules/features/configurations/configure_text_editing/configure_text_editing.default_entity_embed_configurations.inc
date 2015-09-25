<?php
/**
 * @file
 * configure_text_editing.default_entity_embed_configurations.inc
 */

/**
 * Implements hook_default_entity_embed_configuration().
 */
function configure_text_editing_default_entity_embed_configuration() {
  $export = array();

  $configuration = new stdClass();
  $configuration->disabled = FALSE; /* Edit this to true to make a default configuration disabled initially */
  $configuration->api_version = 1;
  $configuration->admin_title = 'Image Gallery';
  $configuration->name = 'image_gallery';
  $configuration->button_label = 'Image Gallery';
  $configuration->entity_type = 'node';
  $configuration->entity_type_bundles = array(
    'image_gallery' => 'image_gallery',
  );
  $configuration->button_icon_fid = 1;
  $export['image_gallery'] = $configuration;

  return $export;
}
