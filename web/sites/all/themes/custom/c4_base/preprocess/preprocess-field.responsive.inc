<?php

/**
 * Remove clearfix from fields with inline labels
 */
function c4_base_alpha_preprocess_field(&$variables) {
  // Add a "clearfix" class to the wrapper since we float the label and the
  // field items in field.css if the label is inline.
  if ($variables['element']['#label_display'] == 'inline') {
    $variables['classes_array'][] = 'clearfix';
    do{
      $index = array_search('clearfix', $variables['classes_array']);
      if ($index !== FALSE){
        unset($variables['classes_array'][$index]);
      }
    } while($index !== false);
  }
}
