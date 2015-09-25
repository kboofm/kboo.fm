<?php
/**
 * @file
 * configure_user_accounts.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function configure_user_accounts_user_default_roles() {
  $roles = array();

  // Exported role: Admin - Developer.
  $roles['Admin - Developer'] = array(
    'name' => 'Admin - Developer',
    'weight' => 13,
  );

  // Exported role: Admin - Site Administrator.
  $roles['Admin - Site Administrator'] = array(
    'name' => 'Admin - Site Administrator',
    'weight' => 11,
  );

  // Exported role: Admin - Station.
  $roles['Admin - Station'] = array(
    'name' => 'Admin - Station',
    'weight' => 12,
  );

  // Exported role: Admin - Web Content Producer.
  $roles['Admin - Web Content Producer'] = array(
    'name' => 'Admin - Web Content Producer',
    'weight' => 10,
  );

  // Exported role: Content Author - Blog.
  $roles['Content Author - Blog'] = array(
    'name' => 'Content Author - Blog',
    'weight' => 6,
  );

  // Exported role: Content Submitter - Standalone Media.
  $roles['Content Submitter - Standalone Media'] = array(
    'name' => 'Content Submitter - Standalone Media',
    'weight' => 7,
  );

  // Exported role: Livewire Reader.
  $roles['Livewire Reader'] = array(
    'name' => 'Livewire Reader',
    'weight' => 5,
  );

  // Exported role: Manager - Calendar.
  $roles['Manager - Calendar'] = array(
    'name' => 'Manager - Calendar',
    'weight' => 9,
  );

  // Exported role: Manager - Standalone Media.
  $roles['Manager - Standalone Media'] = array(
    'name' => 'Manager - Standalone Media',
    'weight' => 8,
  );

  // Exported role: Show Host.
  $roles['Show Host'] = array(
    'name' => 'Show Host',
    'weight' => 3,
  );

  // Exported role: Staff.
  $roles['Staff'] = array(
    'name' => 'Staff',
    'weight' => 4,
  );

  // Exported role: Volunteer.
  $roles['Volunteer'] = array(
    'name' => 'Volunteer',
    'weight' => 2,
  );

  // Exported role: WYSIWYG Access - Advanced.
  $roles['WYSIWYG Access - Advanced'] = array(
    'name' => 'WYSIWYG Access - Advanced',
    'weight' => 15,
  );

  // Exported role: WYSIWYG Access - Simple.
  $roles['WYSIWYG Access - Simple'] = array(
    'name' => 'WYSIWYG Access - Simple',
    'weight' => 14,
  );

  return $roles;
}
