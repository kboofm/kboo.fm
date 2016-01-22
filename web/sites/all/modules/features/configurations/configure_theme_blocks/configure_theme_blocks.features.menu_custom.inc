<?php
/**
 * @file
 * configure_theme_blocks.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function configure_theme_blocks_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-footer-menu-first.
  $menus['menu-footer-menu-first'] = array(
    'menu_name' => 'menu-footer-menu-first',
    'title' => 'Footer Menu First',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-fourth.
  $menus['menu-footer-menu-fourth'] = array(
    'menu_name' => 'menu-footer-menu-fourth',
    'title' => 'Footer Menu Fourth',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-second.
  $menus['menu-footer-menu-second'] = array(
    'menu_name' => 'menu-footer-menu-second',
    'title' => 'Footer Menu Second',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-third.
  $menus['menu-footer-menu-third'] = array(
    'menu_name' => 'menu-footer-menu-third',
    'title' => 'Footer Menu Third',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer Menu First');
  t('Footer Menu Fourth');
  t('Footer Menu Second');
  t('Footer Menu Third');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');

  return $menus;
}
