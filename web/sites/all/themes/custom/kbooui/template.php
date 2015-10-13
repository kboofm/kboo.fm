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
