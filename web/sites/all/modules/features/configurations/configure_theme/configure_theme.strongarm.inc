<?php
/**
 * @file
 * configure_theme.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function configure_theme_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'l, F j, Y - g:ia';
  $export['date_format_long'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long_with_at_text';
  $strongarm->value = 'l, F j, Y \\a\\t g:ia';
  $export['date_format_long_with_at_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'D, m/d/Y - g:ia';
  $export['date_format_medium'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'm/d/Y - g:ia';
  $export['date_format_short'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_jpeg_quality';
  $strongarm->value = '90';
  $export['image_jpeg_quality'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_toolkit';
  $strongarm->value = 'gd';
  $export['image_toolkit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'responsive_favicons_path';
  $strongarm->value = 'favicons';
  $export['responsive_favicons_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'responsive_favicons_remove_default';
  $strongarm->value = 0;
  $export['responsive_favicons_remove_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'responsive_favicons_tags';
  $strongarm->value = array(
    0 => '<link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-57x57.png">',
    1 => '<link rel="apple-touch-icon" sizes="60x60" href="/apple-touch-icon-60x60.png">',
    2 => '<link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-72x72.png">',
    3 => '<link rel="apple-touch-icon" sizes="76x76" href="/apple-touch-icon-76x76.png">',
    4 => '<link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114x114.png">',
    5 => '<link rel="apple-touch-icon" sizes="120x120" href="/apple-touch-icon-120x120.png">',
    6 => '<link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144x144.png">',
    7 => '<link rel="apple-touch-icon" sizes="152x152" href="/apple-touch-icon-152x152.png">',
    8 => '<link rel="icon" type="image/png" href="/favicon-32x32.png" sizes="32x32">',
    9 => '<link rel="icon" type="image/png" href="/favicon-96x96.png" sizes="96x96">',
    10 => '<link rel="icon" type="image/png" href="/favicon-16x16.png" sizes="16x16">',
    11 => '<link rel="manifest" href="/manifest.json">',
    12 => '<link rel="mask-icon" href="/safari-pinned-tab.svg" color="#5bbad5">',
    13 => '<meta name="msapplication-TileColor" content="#da532c">',
    14 => '<meta name="msapplication-TileImage" content="/mstile-144x144.png">',
    15 => '<meta name="theme-color" content="#ffffff">',
    16 => '',
    17 => '<link rel="shortcut icon" href="/favicon.ico" />',
    18 => '<<link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-57x57.png">',
    19 => '<link rel="apple-touch-icon" sizes="60x60" href="/apple-touch-icon-60x60.png">',
    20 => '<link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-72x72.png">',
    21 => '<link rel="apple-touch-icon" sizes="76x76" href="/apple-touch-icon-76x76.png">',
    22 => '<link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114x114.png">',
    23 => '<link rel="apple-touch-icon" sizes="120x120" href="/apple-touch-icon-120x120.png">',
    24 => '<link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144x144.png">',
    25 => '<link rel="apple-touch-icon" sizes="152x152" href="/apple-touch-icon-152x152.png">',
    26 => '<link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon-180x180.png">',
    27 => '<link rel="icon" type="image/png" href="/favicon-32x32.png" sizes="32x32">',
    28 => '<link rel="icon" type="image/png" href="/android-chrome-192x192.png" sizes="192x192">',
    29 => '<link rel="icon" type="image/png" href="/favicon-96x96.png" sizes="96x96">',
    30 => '<link rel="icon" type="image/png" href="/favicon-16x16.png" sizes="16x16">',
    31 => '<link rel="manifest" href="/manifest.json">',
    32 => '<link rel="mask-icon" href="/safari-pinned-tab.svg" color="#5bbad5">',
    33 => '<meta name="msapplication-TileColor" content="#da532c">',
    34 => '<meta name="msapplication-TileImage" content="/mstile-144x144.png">',
    35 => '<meta name="msapplication-config" content="/browserconfig.xml">',
    36 => '<meta name="theme-color" content="#ffffff">',
    37 => '',
    38 => '<!-- IE11 tiles -->',
    39 => '<meta name="msapplication-square70x70logo" content="mstile-70x70.png"/>',
    40 => '<meta name="msapplication-square150x150logo" content="mstile-150x150.png"/>',
    41 => '<meta name="msapplication-wide310x150logo" content="mstile-310x150.png"/>',
    42 => '<meta name="msapplication-square310x310logo" content="mstile-310x310.png"/>',
  );
  $export['responsive_favicons_tags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'responsive_favicons_upload';
  $strongarm->value = '';
  $export['responsive_favicons_upload'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'kbooui';
  $export['theme_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_kbooui_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 0,
    'toggle_slogan' => 0,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 0,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => 'public://kboo-logo.png',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => '',
    'favicon_upload' => '',
    'bootstrap__active_tab' => 'edit-general',
    'bootstrap_fluid_container' => 0,
    'bootstrap_button_size' => '',
    'bootstrap_button_colorize' => 1,
    'bootstrap_button_iconize' => 1,
    'bootstrap_forms_required_has_error' => 0,
    'bootstrap_forms_smart_descriptions' => 1,
    'bootstrap_forms_smart_descriptions_limit' => '250',
    'bootstrap_forms_smart_descriptions_allowed_tags' => 'b, code, em, i, kbd, span, strong',
    'bootstrap_image_shape' => '',
    'bootstrap_image_responsive' => 1,
    'bootstrap_table_bordered' => 0,
    'bootstrap_table_condensed' => 0,
    'bootstrap_table_hover' => 1,
    'bootstrap_table_striped' => 1,
    'bootstrap_table_responsive' => 1,
    'bootstrap_breadcrumb' => '1',
    'bootstrap_breadcrumb_home' => 0,
    'bootstrap_breadcrumb_title' => 1,
    'bootstrap_navbar_position' => '',
    'bootstrap_navbar_inverse' => 0,
    'bootstrap_pager_first_and_last' => 1,
    'bootstrap_region_well-help' => '',
    'bootstrap_region_well-content' => '',
    'bootstrap_region_well-page_top' => '',
    'bootstrap_region_well-page_bottom' => '',
    'bootstrap_anchors_fix' => '0',
    'bootstrap_anchors_smooth_scrolling' => '0',
    'bootstrap_forms_has_error_value_toggle' => 1,
    'bootstrap_popover_enabled' => 1,
    'bootstrap_popover_animation' => 1,
    'bootstrap_popover_html' => 0,
    'bootstrap_popover_placement' => 'right',
    'bootstrap_popover_selector' => '',
    'bootstrap_popover_trigger' => array(
      'click' => 'click',
      'hover' => 0,
      'focus' => 0,
      'manual' => 0,
    ),
    'bootstrap_popover_trigger_autoclose' => 1,
    'bootstrap_popover_title' => '',
    'bootstrap_popover_content' => '',
    'bootstrap_popover_delay' => '0',
    'bootstrap_popover_container' => 'body',
    'bootstrap_tooltip_enabled' => 1,
    'bootstrap_tooltip_animation' => 1,
    'bootstrap_tooltip_html' => 0,
    'bootstrap_tooltip_placement' => 'auto left',
    'bootstrap_tooltip_selector' => '',
    'bootstrap_tooltip_trigger' => array(
      'hover' => 'hover',
      'focus' => 'focus',
      'click' => 0,
      'manual' => 0,
    ),
    'bootstrap_tooltip_delay' => '0',
    'bootstrap_tooltip_container' => 'body',
    'bootstrap_toggle_jquery_error' => 0,
    'bootstrap_cdn_provider' => '',
    'bootstrap_cdn_custom_css' => 'https://cdn.jsdelivr.net/bootstrap/3.3.5/css/bootstrap.css',
    'bootstrap_cdn_custom_css_min' => 'https://cdn.jsdelivr.net/bootstrap/3.3.5/css/bootstrap.min.css',
    'bootstrap_cdn_custom_js' => 'https://cdn.jsdelivr.net/bootstrap/3.3.5/js/bootstrap.js',
    'bootstrap_cdn_custom_js_min' => 'https://cdn.jsdelivr.net/bootstrap/3.3.5/js/bootstrap.min.js',
    'bootstrap_cdn_provider_import_data' => '',
    'bootstrap_cdn_jsdelivr_version' => '3.3.5',
    'bootstrap_cdn_jsdelivr_theme' => 'bootstrap',
  );
  $export['theme_kbooui_settings'] = $strongarm;

  return $export;
}
