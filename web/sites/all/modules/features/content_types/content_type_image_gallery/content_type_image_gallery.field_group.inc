<?php
/**
 * @file
 * content_type_image_gallery.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function content_type_image_gallery_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_bottom|node|image_gallery|form';
  $field_group->group_name = 'group_content_bottom';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content below media',
    'weight' => '2',
    'children' => array(
      0 => 'field_body_below_media',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content-bottom field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content_bottom|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|image_gallery|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_parent_section',
      2 => 'field_short_description',
      3 => 'title_field',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_developer_info|node|image_gallery|form';
  $field_group->group_name = 'group_developer_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Developer info',
    'weight' => '6',
    'children' => array(
      0 => 'field_d6_nid',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-developer-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_developer_info|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallery|node|image_gallery|form';
  $field_group->group_name = 'group_gallery';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Gallery',
    'weight' => '1',
    'children' => array(
      0 => 'field_flickr_photoset',
      1 => 'field_image_files',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gallery field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_gallery|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_info|node|image_gallery|form';
  $field_group->group_name = 'group_profile_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profile info',
    'weight' => '3',
    'children' => array(
      0 => 'field_authored_by',
      1 => 'field_hosted_by',
      2 => 'field_produced_by',
      3 => 'field_produced_for',
      4 => 'field_sponsored_by',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-profile-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_profile_info|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_related|node|image_gallery|form';
  $field_group->group_name = 'group_related';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Related info & topics',
    'weight' => '4',
    'children' => array(
      0 => 'field_related_acts',
      1 => 'field_related_info_content',
      2 => 'field_related_organizations',
      3 => 'field_related_programs',
      4 => 'field_related_show_hosts',
      5 => 'field_topic_tags',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-related field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_related|node|image_gallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaser_info|node|image_gallery|form';
  $field_group->group_name = 'group_teaser_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image_gallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Teaser info',
    'weight' => '5',
    'children' => array(
      0 => 'field_teaser_image',
      1 => 'field_teaser_summary',
      2 => 'field_teaser_title',
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
  $export['group_teaser_info|node|image_gallery|form'] = $field_group;

  return $export;
}
