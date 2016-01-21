<?php
/**
 * @file
 * configure_theme_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function configure_theme_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Footer Contact Info';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'footer_contact';
  $fe_block_boxes->body = '<strong>KBOO Community Radio</strong>
<strong>Office Phone:</strong> 503 231 8032
<strong>Studio Phone:</strong> 503 231 8187
<strong>Fax:</strong> 503 231 7145
20 SE 8th Avenue, Portland, OR 97214
';

  $export['footer_contact'] = $fe_block_boxes;

  return $export;
}
