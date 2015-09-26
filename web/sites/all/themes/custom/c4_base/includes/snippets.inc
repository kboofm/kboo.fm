<?php

/**
 * Ditch the 'all day' label
 */
function ushrn_date_all_day_label() {
	return '';
}

/**
 * Remove language filters from advanced search form
 */
function c4_base_form_alter(&$form, &$form_state, $form_id) {
	if (!user_access('Administer content') && $form_id == 'search_form') {
		unset($form['advanced']['language']);
	}
}

function c4_ms_tile_shit() {
  // Add Microsoft startscreen tiles.
  drupal_add_html_head(array('#type' => 'html_tag','#tag' => 'meta', '#attributes' => array('name' => 'application-name', 'content' => $vars['head_title_array']['name'])),'application_name');
  drupal_add_html_head(array('#type' => 'html_tag','#tag' => 'meta', '#attributes' => array('name' => 'msapplication-TileColor', 'content' => '#0b00a8')),'ms_tile_color');
}
