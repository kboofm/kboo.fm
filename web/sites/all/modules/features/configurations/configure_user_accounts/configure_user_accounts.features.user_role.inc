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
    'weight' => 4,
  );

  // Exported role: Admin - Site Administrator.
  $roles['Admin - Site Administrator'] = array(
    'name' => 'Admin - Site Administrator',
    'weight' => 6,
  );

  // Exported role: Author - Page.
  $roles['Author - Page'] = array(
    'name' => 'Author - Page',
    'weight' => 15,
  );

  // Exported role: Author - Program.
  $roles['Author - Program'] = array(
    'name' => 'Author - Program',
    'weight' => 20,
  );

  // Exported role: Staff.
  $roles['Staff'] = array(
    'name' => 'Staff',
    'weight' => 10,
  );

  return $roles;
}
