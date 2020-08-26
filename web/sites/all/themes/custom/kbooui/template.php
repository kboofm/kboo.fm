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
#dpm('in pp html');
#dpm($variables, 'vars');
#dpm($variables['head'], 'vhead');
}
/*
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
*/

/*
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
*/

function kbooui_preprocess_book_navigation(&$variables) {
  $book_link = $variables['book_link'];

  // Provide extra variables for themers. Not needed by default.
  $variables['book_id'] = $book_link['bid'];
  $variables['book_title'] = check_plain($book_link['link_title']);
  $variables['book_url'] = 'node/' . $book_link['bid'];
  $variables['current_depth'] = $book_link['depth'];
  $variables['tree'] = '';

  if ($book_link['mlid']) {
    $variables['tree'] = book_children($book_link);
/*
dpm($book_link);
$j = book_children($book_link);
dpm($j);
*/
/*
$foo = book_get_flat_menu($book_link);
dpm($foo);
	foreach($foo as $bl)
	{
		$variables['tree'] .= book_children($bl);
	}
*/

    if ($prev = book_prev($book_link)) {
      $prev_href = url($prev['href']);
      drupal_add_html_head_link(array('rel' => 'prev', 'href' => $prev_href));
      $variables['prev_url'] = $prev_href;
      $variables['prev_title'] = check_plain($prev['title']);
    }

    if ($book_link['plid'] && $parent = book_link_load($book_link['plid'])) {
      $parent_href = url($parent['href']);
      drupal_add_html_head_link(array('rel' => 'up', 'href' => $parent_href));
      $variables['parent_url'] = $parent_href;
      $variables['parent_title'] = check_plain($parent['title']);
    }

    if ($next = book_next($book_link)) {
      $next_href = url($next['href']);
      drupal_add_html_head_link(array('rel' => 'next', 'href' => $next_href));
      $variables['next_url'] = $next_href;
      $variables['next_title'] = check_plain($next['title']);
    }
  }

  $variables['has_links'] = FALSE;
  // Link variables to filter for values and set state of the flag variable.
  $links = array('prev_url', 'prev_title', 'parent_url', 'parent_title', 'next_url', 'next_title');
  foreach ($links as $link) {
    if (isset($variables[$link])) {
      // Flag when there is a value.
      $variables['has_links'] = TRUE;
    }
    else {
      // Set empty to prevent notices.
      $variables[$link] = '';
    }
  }
}
