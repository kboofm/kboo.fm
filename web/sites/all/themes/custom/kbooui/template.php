<?php

/**
 * @file
 * template.php
 */

/**
* Process variables for search-result.tpl.php.
*
* @see search-result.tpl.php
*/
function kbooui_preprocess_search_result(&$variables) {
  // Do not display user name and modification date and number of comments from search results
  $variables['info'] = '';
}

function kbooui_preprocess_html(&$variables)
{
	$cpv = views_get_page_view();
	if(!is_object($cpv))
	{
		return;
	}
	if($cpv->name == 'slideshow_view' && $cpv->current_display == 'page') #set these to suit your view
	{
		$variables['theme_hook_suggestions'][] = 'html__notheme';
	}
}

function kbooui_preprocess_page(&$variables)
{
  // Move some variables to the top level for themer convenience and template cleanliness.
  $variables['show_messages'] = $variables['page']['#show_messages'];

  foreach (system_region_list($GLOBALS['theme'], REGIONS_ALL, FALSE) as $region_key) {
    if (!isset($variables['page'][$region_key])) {
      $variables['page'][$region_key] = array();
    }
    if ($region_content = drupal_get_region_content($region_key)) {
      $variables['page'][$region_key][]['#markup'] = $region_content;
    }
  }

  // Set up layout variable.
  $variables['layout'] = 'none';
  if (!empty($variables['page']['sidebar_first'])) {
    $variables['layout'] = 'first';
  }
  if (!empty($variables['page']['sidebar_second'])) {
    $variables['layout'] = ($variables['layout'] == 'first') ? 'both' : 'second';
  }

  $variables['base_path'] = base_path();
  $variables['front_page'] = url();
  $variables['feed_icons'] = drupal_get_feeds();
  $variables['language'] = $GLOBALS['language'];
  $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['logo'] = theme_get_setting('logo');
  $variables['main_menu'] = theme_get_setting('toggle_main_menu') ? menu_main_menu() : array();
  $variables['secondary_menu'] = theme_get_setting('toggle_secondary_menu') ? menu_secondary_menu() : array();
  $variables['action_links'] = menu_local_actions();
  $variables['site_name'] = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');
  $variables['site_slogan'] = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $variables['tabs'] = menu_local_tabs();

  if ($node = menu_get_object()) {
    $variables['node'] = $node;
  }

  // Populate the page template suggestions.
  if ($suggestions = theme_get_suggestions(arg(), 'page')) {
    $variables['theme_hook_suggestions'] = $suggestions;
  }

	#edits
	$cpv = views_get_page_view();
	if($cpv->name == 'slideshow_view' && $cpv->current_display == 'page')
	{
		$variables['theme_hook_suggestions'][] = 'page__notheme';
	}
}
