<?php
/**
 * @file
 * configure_user_accounts.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function configure_user_accounts_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access ad node'.
  $permissions['access ad node'] = array(
    'name' => 'access ad node',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'simpleads',
  );

  // Exported permission: 'access ad statistics'.
  $permissions['access ad statistics'] = array(
    'name' => 'access ad statistics',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'simpleads',
  );

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'views',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'media',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access printer-friendly version'.
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(),
    'module' => 'book',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'add content to books'.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'book',
  );

  // Exported permission: 'add media from remote sources'.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'media_internet',
  );

  // Exported permission: 'add media from remote urls'.
  $permissions['add media from remote urls'] = array(
    'name' => 'add media from remote urls',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'remote_stream_wrapper',
  );

  // Exported permission: 'administer @font-your-face'.
  $permissions['administer @font-your-face'] = array(
    'name' => 'administer @font-your-face',
    'roles' => array(),
    'module' => 'fontyourface',
  );

  // Exported permission: 'administer CAPTCHA settings'.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'administer Terms and Conditions'.
  $permissions['administer Terms and Conditions'] = array(
    'name' => 'administer Terms and Conditions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'legal',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer book outlines'.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer ckeditor'.
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'ckeditor',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'field_group',
  );

  // Exported permission: 'administer file types'.
  $permissions['administer file types'] = array(
    'name' => 'administer file types',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'administer files'.
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'image',
  );

  // Exported permission: 'administer imce'.
  $permissions['administer imce'] = array(
    'name' => 'administer imce',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'imce',
  );

  // Exported permission: 'administer linkit'.
  $permissions['administer linkit'] = array(
    'name' => 'administer linkit',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'linkit',
  );

  // Exported permission: 'administer media browser'.
  $permissions['administer media browser'] = array(
    'name' => 'administer media browser',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'media',
  );

  // Exported permission: 'administer media oembed'.
  $permissions['administer media oembed'] = array(
    'name' => 'administer media oembed',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'media_oembed',
  );

  // Exported permission: 'administer media wysiwyg view mode'.
  $permissions['administer media wysiwyg view mode'] = array(
    'name' => 'administer media wysiwyg view mode',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'media_wysiwyg_view_mode',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer meta tags'.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer publication date'.
  $permissions['administer publication date'] = array(
    'name' => 'administer publication date',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'publication_date',
  );

  // Exported permission: 'administer recaptcha'.
  $permissions['administer recaptcha'] = array(
    'name' => 'administer recaptcha',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'recaptcha',
  );

  // Exported permission: 'administer redirects'.
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'redirect',
  );

  // Exported permission: 'administer responsive favicons'.
  $permissions['administer responsive favicons'] = array(
    'name' => 'administer responsive favicons',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'responsive_favicons',
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

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'views',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass file access'.
  $permissions['bypass file access'] = array(
    'name' => 'bypass file access',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'count ad clicks'.
  $permissions['count ad clicks'] = array(
    'name' => 'count ad clicks',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'simpleads',
  );

  // Exported permission: 'count ad impressions'.
  $permissions['count ad impressions'] = array(
    'name' => 'count ad impressions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'simpleads',
  );

  // Exported permission: 'create basic_page content'.
  $permissions['create basic_page content'] = array(
    'name' => 'create basic_page content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create blog_post content'.
  $permissions['create blog_post content'] = array(
    'name' => 'create blog_post content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create book content'.
  $permissions['create book content'] = array(
    'name' => 'create book content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create event content'.
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create files'.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'create new books'.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'book',
  );

  // Exported permission: 'create organization content'.
  $permissions['create organization content'] = array(
    'name' => 'create organization content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create person_profile content'.
  $permissions['create person_profile content'] = array(
    'name' => 'create person_profile content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create program content'.
  $permissions['create program content'] = array(
    'name' => 'create program content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create promo content'.
  $permissions['create promo content'] = array(
    'name' => 'create promo content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create scheduled_timeslot content'.
  $permissions['create scheduled_timeslot content'] = array(
    'name' => 'create scheduled_timeslot content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create simpleads content'.
  $permissions['create simpleads content'] = array(
    'name' => 'create simpleads content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create station_content content'.
  $permissions['create station_content content'] = array(
    'name' => 'create station_content content',
    'roles' => array(
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'customize ckeditor'.
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(),
    'module' => 'ckeditor',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any audio files'.
  $permissions['delete any audio files'] = array(
    'name' => 'delete any audio files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any basic_page content'.
  $permissions['delete any basic_page content'] = array(
    'name' => 'delete any basic_page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any blog_post content'.
  $permissions['delete any blog_post content'] = array(
    'name' => 'delete any blog_post content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any book content'.
  $permissions['delete any book content'] = array(
    'name' => 'delete any book content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any document files'.
  $permissions['delete any document files'] = array(
    'name' => 'delete any document files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any event content'.
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any image files'.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any organization content'.
  $permissions['delete any organization content'] = array(
    'name' => 'delete any organization content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any person_profile content'.
  $permissions['delete any person_profile content'] = array(
    'name' => 'delete any person_profile content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any program content'.
  $permissions['delete any program content'] = array(
    'name' => 'delete any program content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any promo content'.
  $permissions['delete any promo content'] = array(
    'name' => 'delete any promo content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any scheduled_timeslot content'.
  $permissions['delete any scheduled_timeslot content'] = array(
    'name' => 'delete any scheduled_timeslot content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any simpleads content'.
  $permissions['delete any simpleads content'] = array(
    'name' => 'delete any simpleads content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any station_content content'.
  $permissions['delete any station_content content'] = array(
    'name' => 'delete any station_content content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any video files'.
  $permissions['delete any video files'] = array(
    'name' => 'delete any video files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own audio files'.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own basic_page content'.
  $permissions['delete own basic_page content'] = array(
    'name' => 'delete own basic_page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own blog_post content'.
  $permissions['delete own blog_post content'] = array(
    'name' => 'delete own blog_post content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own book content'.
  $permissions['delete own book content'] = array(
    'name' => 'delete own book content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own document files'.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own event content'.
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own organization content'.
  $permissions['delete own organization content'] = array(
    'name' => 'delete own organization content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own person_profile content'.
  $permissions['delete own person_profile content'] = array(
    'name' => 'delete own person_profile content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own program content'.
  $permissions['delete own program content'] = array(
    'name' => 'delete own program content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own promo content'.
  $permissions['delete own promo content'] = array(
    'name' => 'delete own promo content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own scheduled_timeslot content'.
  $permissions['delete own scheduled_timeslot content'] = array(
    'name' => 'delete own scheduled_timeslot content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own simpleads content'.
  $permissions['delete own simpleads content'] = array(
    'name' => 'delete own simpleads content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own station_content content'.
  $permissions['delete own station_content content'] = array(
    'name' => 'delete own station_content content',
    'roles' => array(
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own video files'.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(),
    'module' => 'admin_menu',
  );

  // Exported permission: 'download any audio files'.
  $permissions['download any audio files'] = array(
    'name' => 'download any audio files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any document files'.
  $permissions['download any document files'] = array(
    'name' => 'download any document files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any image files'.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any video files'.
  $permissions['download any video files'] = array(
    'name' => 'download any video files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own audio files'.
  $permissions['download own audio files'] = array(
    'name' => 'download own audio files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own document files'.
  $permissions['download own document files'] = array(
    'name' => 'download own document files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own image files'.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own video files'.
  $permissions['download own video files'] = array(
    'name' => 'download own video files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any audio files'.
  $permissions['edit any audio files'] = array(
    'name' => 'edit any audio files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any basic_page content'.
  $permissions['edit any basic_page content'] = array(
    'name' => 'edit any basic_page content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any blog_post content'.
  $permissions['edit any blog_post content'] = array(
    'name' => 'edit any blog_post content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any book content'.
  $permissions['edit any book content'] = array(
    'name' => 'edit any book content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any document files'.
  $permissions['edit any document files'] = array(
    'name' => 'edit any document files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any event content'.
  $permissions['edit any event content'] = array(
    'name' => 'edit any event content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any image files'.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any organization content'.
  $permissions['edit any organization content'] = array(
    'name' => 'edit any organization content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any person_profile content'.
  $permissions['edit any person_profile content'] = array(
    'name' => 'edit any person_profile content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any program content'.
  $permissions['edit any program content'] = array(
    'name' => 'edit any program content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any promo content'.
  $permissions['edit any promo content'] = array(
    'name' => 'edit any promo content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any scheduled_timeslot content'.
  $permissions['edit any scheduled_timeslot content'] = array(
    'name' => 'edit any scheduled_timeslot content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any simpleads content'.
  $permissions['edit any simpleads content'] = array(
    'name' => 'edit any simpleads content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any station_content content'.
  $permissions['edit any station_content content'] = array(
    'name' => 'edit any station_content content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any video files'.
  $permissions['edit any video files'] = array(
    'name' => 'edit any video files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit meta tags'.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'edit own audio files'.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own basic_page content'.
  $permissions['edit own basic_page content'] = array(
    'name' => 'edit own basic_page content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blog_post content'.
  $permissions['edit own blog_post content'] = array(
    'name' => 'edit own blog_post content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own book content'.
  $permissions['edit own book content'] = array(
    'name' => 'edit own book content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own document files'.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own event content'.
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own organization content'.
  $permissions['edit own organization content'] = array(
    'name' => 'edit own organization content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own person_profile content'.
  $permissions['edit own person_profile content'] = array(
    'name' => 'edit own person_profile content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own program content'.
  $permissions['edit own program content'] = array(
    'name' => 'edit own program content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own promo content'.
  $permissions['edit own promo content'] = array(
    'name' => 'edit own promo content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own scheduled_timeslot content'.
  $permissions['edit own scheduled_timeslot content'] = array(
    'name' => 'edit own scheduled_timeslot content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own simpleads content'.
  $permissions['edit own simpleads content'] = array(
    'name' => 'edit own simpleads content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own station_content content'.
  $permissions['edit own station_content content'] = array(
    'name' => 'edit own station_content content',
    'roles' => array(
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own video files'.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit webform components'.
  $permissions['edit webform components'] = array(
    'name' => 'edit webform components',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
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

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'set any published on date'.
  $permissions['set any published on date'] = array(
    'name' => 'set any published on date',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'publication_date',
  );

  // Exported permission: 'set basic_page published on date'.
  $permissions['set basic_page published on date'] = array(
    'name' => 'set basic_page published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set blog_post published on date'.
  $permissions['set blog_post published on date'] = array(
    'name' => 'set blog_post published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set book published on date'.
  $permissions['set book published on date'] = array(
    'name' => 'set book published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set event published on date'.
  $permissions['set event published on date'] = array(
    'name' => 'set event published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set organization published on date'.
  $permissions['set organization published on date'] = array(
    'name' => 'set organization published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set person_profile published on date'.
  $permissions['set person_profile published on date'] = array(
    'name' => 'set person_profile published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set program published on date'.
  $permissions['set program published on date'] = array(
    'name' => 'set program published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set promo published on date'.
  $permissions['set promo published on date'] = array(
    'name' => 'set promo published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set scheduled_timeslot published on date'.
  $permissions['set scheduled_timeslot published on date'] = array(
    'name' => 'set scheduled_timeslot published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set simpleads published on date'.
  $permissions['set simpleads published on date'] = array(
    'name' => 'set simpleads published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set station_content published on date'.
  $permissions['set station_content published on date'] = array(
    'name' => 'set station_content published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'set webform published on date'.
  $permissions['set webform published on date'] = array(
    'name' => 'set webform published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  // Exported permission: 'show format selection for comment'.
  $permissions['show format selection for comment'] = array(
    'name' => 'show format selection for comment',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for file'.
  $permissions['show format selection for file'] = array(
    'name' => 'show format selection for file',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for node'.
  $permissions['show format selection for node'] = array(
    'name' => 'show format selection for node',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for taxonomy_term'.
  $permissions['show format selection for taxonomy_term'] = array(
    'name' => 'show format selection for taxonomy_term',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for user'.
  $permissions['show format selection for user'] = array(
    'name' => 'show format selection for user',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format tips'.
  $permissions['show format tips'] = array(
    'name' => 'show format tips',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show more format tips link'.
  $permissions['show more format tips link'] = array(
    'name' => 'show more format tips link',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'skip CAPTCHA'.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'use PHP for title patterns'.
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(),
    'module' => 'auto_nodetitle',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use ctools import'.
  $permissions['use ctools import'] = array(
    'name' => 'use ctools import',
    'roles' => array(),
    'module' => 'ctools',
  );

  // Exported permission: 'use media wysiwyg'.
  $permissions['use media wysiwyg'] = array(
    'name' => 'use media wysiwyg',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'media_wysiwyg',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html_no_wysiwyg'.
  $permissions['use text format full_html_no_wysiwyg'] = array(
    'name' => 'use text format full_html_no_wysiwyg',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html_simple_wysiwyg'.
  $permissions['use text format full_html_simple_wysiwyg'] = array(
    'name' => 'use text format full_html_simple_wysiwyg',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view Terms and Conditions'.
  $permissions['view Terms and Conditions'] = array(
    'name' => 'view Terms and Conditions',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'legal',
  );

  // Exported permission: 'view files'.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own files'.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own private files'.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view private files'.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'Admin - Developer' => 'Admin - Developer',
      'Admin - Site Administrator' => 'Admin - Site Administrator',
      'Author - Page' => 'Author - Page',
      'Author - Program' => 'Author - Program',
      'Staff' => 'Staff',
    ),
    'module' => 'system',
  );

  return $permissions;
}
