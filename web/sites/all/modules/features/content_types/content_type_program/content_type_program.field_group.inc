<?php
/**
 * @file
 * content_type_program.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function content_type_program_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_bottom|node|program|form';
  $field_group->group_name = 'group_content_bottom';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content below media',
    'weight' => '3',
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
  $export['group_content_bottom|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|program|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_parent_section',
      2 => 'field_program_type',
      3 => 'field_short_description',
      4 => 'title_field',
      5 => 'field_episode_record',
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
  $export['group_content|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_developer_info|node|program|form';
  $field_group->group_name = 'group_developer_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Developer info',
    'weight' => '7',
    'children' => array(
      0 => 'field_d6_nid',
      1 => 'field_published_date',
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
  $export['group_developer_info|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|program|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '1',
    'children' => array(
      0 => 'field_lead_image',
      1 => 'field_more_images',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-images field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_images|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|program|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '2',
    'children' => array(
      0 => 'field_audio_files',
      1 => 'field_files',
      2 => 'field_links',
      3 => 'field_video_files',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-media field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_media|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_info|node|program|form';
  $field_group->group_name = 'group_profile_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profile info',
    'weight' => '4',
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
  $export['group_profile_info|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_related|node|program|form';
  $field_group->group_name = 'group_related';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Related info & topics',
    'weight' => '5',
    'children' => array(
      0 => 'field_genres',
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
  $export['group_related|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaser_info|node|program|form';
  $field_group->group_name = 'group_teaser_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Teaser info',
    'weight' => '6',
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
  $export['group_teaser_info|node|program|form'] = $field_group;

  return $export;
}
