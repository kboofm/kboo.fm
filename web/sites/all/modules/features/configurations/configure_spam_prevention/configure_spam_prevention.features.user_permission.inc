<?php
/**
 * @file
 * configure_spam_prevention.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function configure_spam_prevention_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer CAPTCHA settings'.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'administer recaptcha'.
  $permissions['administer recaptcha'] = array(
    'name' => 'administer recaptcha',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'recaptcha',
  );

  // Exported permission: 'skip CAPTCHA'.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'captcha',
  );

  return $permissions;
}
