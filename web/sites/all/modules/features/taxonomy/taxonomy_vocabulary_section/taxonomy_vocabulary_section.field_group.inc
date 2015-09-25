<?php
/**
 * @file
 * taxonomy_vocabulary_section.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function taxonomy_vocabulary_section_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsorship_info|taxonomy_term|sections|form';
  $field_group->group_name = 'group_sponsorship_info';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'sections';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sponsorship info',
    'weight' => '6',
    'children' => array(
      0 => 'field_sponsored_by_image',
      1 => 'field_sponsored_by_text',
      2 => 'field_sponsored_by',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Sponsorship info',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-sponsorship-info field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_sponsorship_info|taxonomy_term|sections|form'] = $field_group;

  return $export;
}
