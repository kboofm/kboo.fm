<?php
/**
 * @file
 * content_type_promo.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function content_type_promo_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaser_info|node|promo|form';
  $field_group->group_name = 'group_teaser_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'promo';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Teaser info',
    'weight' => '1',
    'children' => array(
      0 => 'field_link',
      1 => 'field_teaser_title',
      2 => 'field_teaser_image',
      3 => 'field_teaser_summary',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-teaser-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_teaser_info|node|promo|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Teaser info');

  return $field_groups;
}
