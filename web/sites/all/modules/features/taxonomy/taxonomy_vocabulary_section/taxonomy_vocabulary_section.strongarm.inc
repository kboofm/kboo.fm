<?php
/**
 * @file
 * taxonomy_vocabulary_section.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function taxonomy_vocabulary_section_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_sections_pattern';
  $strongarm->value = 'section-url/[term:field-parent-section:field-landing-page:url:path]/[term:field-landing-page:url:path]';
  $export['pathauto_taxonomy_term_sections_pattern'] = $strongarm;

  return $export;
}
