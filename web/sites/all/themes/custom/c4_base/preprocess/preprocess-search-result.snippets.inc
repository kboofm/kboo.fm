<?php 


/**
* Process variables for search-result.tpl.php.
*
* @see search-result.tpl.php
*/
function c4_base_alpha_preprocess_search_result(&$variables) {
  // Remove user name and modification date from search results
  $variables['info'] = '';
}
