<?php


/**
 * Override default image output to remove inline width and height
 * for responsive image possibilities
 */
function c4_base_image($variables) {
	$attributes = $variables['attributes'];
	$attributes['src'] = file_create_url($variables['path']);

	foreach (array('alt', 'title') as $key) {

		if (isset($variables[$key])) {
			$attributes[$key] = $variables[$key];
		}
	}

	return '<img' . drupal_attributes($attributes) . ' />';
}
