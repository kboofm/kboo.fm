<?php
/**
 * @file
 * configure_search.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function configure_search_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer search_restrict'.
  $permissions['administer search_restrict'] = array(
    'name' => 'administer search_restrict',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'search_restrict',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Admin - Web Content Producer' => 'Admin - Web Content Producer',
    ),
    'module' => 'path',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Web Content Producer' => 'Admin - Web Content Producer',
    ),
    'module' => 'search',
  );

  return $permissions;
}
