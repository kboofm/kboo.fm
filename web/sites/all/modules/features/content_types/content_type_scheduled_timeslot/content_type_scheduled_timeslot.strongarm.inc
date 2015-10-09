<?php
/**
 * @file
 * content_type_scheduled_timeslot.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function content_type_scheduled_timeslot_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_scheduled_timeslot';
  $strongarm->value = 0;
  $export['comment_anonymous_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_scheduled_timeslot';
  $strongarm->value = 1;
  $export['comment_default_mode_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_scheduled_timeslot';
  $strongarm->value = '50';
  $export['comment_default_per_page_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_scheduled_timeslot';
  $strongarm->value = 1;
  $export['comment_form_location_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_scheduled_timeslot';
  $strongarm->value = '1';
  $export['comment_preview_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_scheduled_timeslot';
  $strongarm->value = '1';
  $export['comment_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_scheduled_timeslot';
  $strongarm->value = 1;
  $export['comment_subject_field_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__scheduled_timeslot';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '5',
        ),
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_scheduled_timeslot';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_scheduled_timeslot';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_scheduled_timeslot';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_scheduled_timeslot';
  $strongarm->value = '1';
  $export['node_preview_scheduled_timeslot'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_scheduled_timeslot';
  $strongarm->value = 1;
  $export['node_submitted_scheduled_timeslot'] = $strongarm;

  return $export;
}
