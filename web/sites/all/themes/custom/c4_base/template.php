<?php

/**
 *  Adding current page user is on to the trail
 */
function c4_base__breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumb[] = drupal_get_title();
    $output .= '<div class="breadcrumb">' . implode(' &raquo; ', $breadcrumb) . '</div>';
    return $output;
  }
}


