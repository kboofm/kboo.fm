<?php

/**
 * @file
 *   As sample add-on theme for the terms page.
 *   Theming recommendations are to use PHP within HTML, although
 *   pure PHP works (but slower).
 *
 * @param $variables[0]
 *   The complete enhanced terms tree.
 * @param $variables[1]
 *   The number of cells per row for tables.
 * @param $variables[2]
 *   The list mode setting. 0 => Hierarchical; 1 => Flat.
 *
 * @return - none -
 *   This code must output (echo or print) the contents to the page.
 */
//  drupal_set_message('taxonomy_list_nancy.tpl.php');
//  echo 'taxonomy_list_nancy.tpl.php';
//  print '<pre>'. print_r(get_defined_vars(), true) .'</pre>';
  $terms = $variables[0];
  $rows = array();
  foreach ($terms as $tid => $term) {
    $rows[] = array(
      decode_entities(l(str_repeat('&bull;', $term->depth) . $term->name, taxonomy_get_path($tid))),
      taxonomy_term_count_nodes($tid),
      );
  }
  echo theme('table', array('Name', 'Count'), $rows, array('style' => 'width: auto;'));
