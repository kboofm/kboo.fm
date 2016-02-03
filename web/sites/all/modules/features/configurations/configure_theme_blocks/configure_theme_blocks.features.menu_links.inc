<?php
/**
 * @file
 * configure_theme_blocks.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function configure_theme_blocks_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_about-link-1-link-1:<front>.
  $menu_links['main-menu_about-link-1-link-1:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About Link 1 Link 1',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_about-link-1-link-1:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_about-link-1:<front>',
  );
  // Exported menu link: main-menu_about-link-1:<front>.
  $menu_links['main-menu_about-link-1:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About Link 1',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_about-link-1:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_about:<front>',
  );
  // Exported menu link: main-menu_about-link-2:<front>.
  $menu_links['main-menu_about-link-2:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About Link 2',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_about-link-2:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_about:<front>',
  );
  // Exported menu link: main-menu_about:<front>.
  $menu_links['main-menu_about:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About',
    'options' => array(
      'identifier' => 'main-menu_about:<front>',
      'attributes' => array(
        'class' => array(
          0 => 'dropdown-toggle',
        ),
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => 'dropdown',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: main-menu_events:<front>.
  $menu_links['main-menu_events:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_events:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_get-involved:<front>.
  $menu_links['main-menu_get-involved:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Get Involved',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_get-involved:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_longer-about-link-3-goes-here:<front>.
  $menu_links['main-menu_longer-about-link-3-goes-here:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Longer about link 3 goes here',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_longer-about-link-3-goes-here:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_about:<front>',
  );
  // Exported menu link: main-menu_programs:<front>.
  $menu_links['main-menu_programs:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Programs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_programs:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_support:<front>.
  $menu_links['main-menu_support:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Support',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_support:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-first_one:<front>.
  $menu_links['menu-footer-menu-first_one:<front>'] = array(
    'menu_name' => 'menu-footer-menu-first',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'One',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-first_one:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-first_three:<front>.
  $menu_links['menu-footer-menu-first_three:<front>'] = array(
    'menu_name' => 'menu-footer-menu-first',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Three',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-first_three:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-first_two:<front>.
  $menu_links['menu-footer-menu-first_two:<front>'] = array(
    'menu_name' => 'menu-footer-menu-first',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Two',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-first_two:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-fourth_one:<front>.
  $menu_links['menu-footer-menu-fourth_one:<front>'] = array(
    'menu_name' => 'menu-footer-menu-fourth',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'One',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-fourth_one:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-fourth_three:<front>.
  $menu_links['menu-footer-menu-fourth_three:<front>'] = array(
    'menu_name' => 'menu-footer-menu-fourth',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Three',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-fourth_three:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-fourth_two:<front>.
  $menu_links['menu-footer-menu-fourth_two:<front>'] = array(
    'menu_name' => 'menu-footer-menu-fourth',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Two',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-fourth_two:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-second_one:<front>.
  $menu_links['menu-footer-menu-second_one:<front>'] = array(
    'menu_name' => 'menu-footer-menu-second',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'One',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-second_one:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-second_three:<front>.
  $menu_links['menu-footer-menu-second_three:<front>'] = array(
    'menu_name' => 'menu-footer-menu-second',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Three',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-second_three:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-second_two:<front>.
  $menu_links['menu-footer-menu-second_two:<front>'] = array(
    'menu_name' => 'menu-footer-menu-second',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Two',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-second_two:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-third_one:<front>.
  $menu_links['menu-footer-menu-third_one:<front>'] = array(
    'menu_name' => 'menu-footer-menu-third',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'One',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-third_one:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-third_three:<front>.
  $menu_links['menu-footer-menu-third_three:<front>'] = array(
    'menu_name' => 'menu-footer-menu-third',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Three',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-third_three:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu-third_two:<front>.
  $menu_links['menu-footer-menu-third_two:<front>'] = array(
    'menu_name' => 'menu-footer-menu-third',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Two',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu-third_two:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('About Link 1');
  t('About Link 1 Link 1');
  t('About Link 2');
  t('Events');
  t('Get Involved');
  t('Longer about link 3 goes here');
  t('One');
  t('Programs');
  t('Support');
  t('Three');
  t('Two');

  return $menu_links;
}
