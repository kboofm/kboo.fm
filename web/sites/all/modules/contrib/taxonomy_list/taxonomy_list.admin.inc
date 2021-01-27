<?php

/**
 * @file
 *   Admin stuff for Taxonomy List.
 */

/**
 * Menu callback; presents the admin settings form.
 */
function taxonomy_list_admin_settings() {
  $form = array();
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'taxonomy_list') . '/taxonomy_list.css'
    );
  $noyes = array(0 => t('No'), 1 => t('Yes'));

  $form['taxonomy_list_info'] = array(
    '#value' => t('<p>The taxonomy_list module enable the URL to browse into each vocabulary, using the format of :</p>')
      .  t('<code>"taxonomy/vocabulary/&lt;vid&gt;"</code>')
      .  t('<p>Together with the taxonomy_image.module, the list can be displayed with a image icon.</p>')
    );

  // General settings.
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    );

  $sep_opts = array(
    ' & ' => 'ampersand (&amp;)',
    ' | ' => 'vertical bar (pipe)',
    ', ' => 'comma (,)',
    ' &bull; ' => 'bullet',
    ' &#8211; ' => 'en-dash (&#8211;)',
    ' &#8212; ' => 'em-dash (&#8212;)',
    ' _ ' => 'underscore',
    );

  $form['general']['taxonomy_list_title_separator'] = array(
    '#type' => 'radios',
    '#title' => t('Title separator'),
    '#default_value' => variable_get('taxonomy_list_title_separator', ' & '),
    '#options' => $sep_opts,
    '#description' => t('This is the character that separates multiple vocabulary names in the page title.'),
    '#prefix' => '<div class="taxonomy_list_radios">',
    '#suffix' => '</div>',
    );

  $theme_opts = array(
      'table' => t('Table - Show terms in a table (legacy method).'),
      'list' => t('List - Show terms as a list.'),
      'directory' => t('Directory - Show terms as a directory of content.'),
      );

  $form['general']['taxonomy_list_format'] = array(
    '#type' => 'radios',
    '#title' => t('List Format'),
    '#default_value' => variable_get('taxonomy_list_format', 'table'),
    '#options' => $theme_opts,
    '#description' => t('The method, or layout, for displaying the terms.'),
    );

  $form['general']['taxonomy_list_cell_per_row'] = array(
    '#type' => 'textfield',
    '#title' => t('Terms per row'),
    '#size' => 5,
    '#default_value' => variable_get('taxonomy_list_cell_per_row', 2),
    '#description' => t('Number of terms to be displayed on the same row.'),
    '#states' => array(
      'visible' => array(
        ':input[name="taxonomy_list_format"]' => array('value' => 'table'),
        ),
      ),
    );

  $form['general']['taxonomy_list_list_mode'] = array(
    '#type' => 'radios',
    '#title' => t('List Mode'),
    '#default_value' => variable_get('taxonomy_list_list_mode', 0),
    '#options' => array(
        '0' => t("Hierarchical - Subcategories set off to show the hierarchy."),
        '1' => t('Flat - All terms are listed as the same level in the grid.'),
      ),
    '#description' => t('Whether Taxonomy List displays the hierarchy of the terms.'),
    );

  $filter_list = filter_formats();
  $filters = array();
  foreach ($filter_list as $filter) {
    $filters[$filter->format] = $filter->name;
  }

  $form['general']['taxonomy_list_filter'] = array(
    '#type' => 'radios',
    '#options' => $filters,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Filter for display'),
    '#default_value' => variable_get('taxonomy_list_filter', variable_get('filter_default_format', 1)),
    '#description' => t('For your security, the term names and descriptions are filtered. This option selects which input format will be used.'),
    );
  if (!user_access('administer filters')) {
    $form['general']['taxonomy_list_filter']['#description'] .= ' ' . t('Note: you are not seeing a complete list of filters because you do not have the "administer filters" permission.');
  }

  // @TODO: why is the default not showing?
  $form['general']['taxonomy_list_show_description'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#title' => t('Show parent descriptions?'),
    '#default_value' => (int) variable_get('taxonomy_list_show_description', 1),
    '#description' => t('Should we display the description with parent terms in the directory view?'),
    '#attributes' => array('class' => array('container-inline')),
    );

  // Link settings.
  $form['link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );

  $form['link']['taxonomy_list_edit_link'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Add "edit term" link'),
    '#default_value' => (int) variable_get('taxonomy_list_edit_link', FALSE),
    '#description' => t('Should I add an "edit term" link to the display for authorized users?'),
    );

  if (module_exists('search')) {
    $form['link']['taxonomy_list_search_link'] = array(
      '#type' => 'radios',
      '#options' => $noyes,
      '#attributes' => array('class' => array('container-inline')),
      '#title' => t('Add "search for term" link'),
      '#default_value' => (int) variable_get('taxonomy_list_search_link', FALSE),
      '#description' => t('Should I add an "search for term" link to the display for authorized users?'),
      );
  }

  $form['link']['taxonomy_list_rss_link'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Add RSS link'),
    '#default_value' => (int) variable_get('taxonomy_list_rss_link', FALSE),
    '#description' => t('Should I add an RSS link (icon) to the display?'),
    );

  $form['link']['taxonomy_list_show_children'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Show children when clicked'),
    '#default_value' => (int) variable_get('taxonomy_list_show_children', FALSE),
    '#description' => t('If this is a parent term, show the content for children when the link is clicked upon?'),
    );

  // Optional settings.
  $form['optional'] = array(
    '#type' => 'fieldset',
    '#title' => t('Optional information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );

  $form['optional']['taxonomy_list_term_description'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Show term descriptions'),
    '#default_value' => (int) variable_get('taxonomy_list_term_description', TRUE),
    '#description' => t('Do you want the term descriptions shown?'),
    );

  $form['optional']['taxonomy_list_show_parents'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Show parents of the term'),
    '#default_value' => (int) variable_get('taxonomy_list_show_parents', FALSE),
    '#description' => t('If this is a child term, show the parent structure?'),
    );

  // Counting settings.
  $form['count'] = array(
    '#type' => 'fieldset',
    '#title' => t('Count content'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );

  $count_opts = array(
    'none' => t('No count.'),
    'all' => t('Count all content types.'),
    'by_type' => t('Count by content type.'),
    'not_zero' => t("Count by type, don't show zero counts."),
    );

  $form['count']['taxonomy_list_count'] = array(
    '#type' => 'radios',
    '#title' => t('Count content types'),
    '#default_value' => (int) variable_get('taxonomy_list_count', 0),
    '#options' => $count_opts,
    '#description' => t('How Taxonomy List counts the content types for terms.'),
    '#prefix' => '<div class="taxonomy_list_radios">',
    '#suffix' => '</div>',
    );

  if (module_exists('node_type_filter')) {
    $form['count']['taxonomy_list_count']['#description'] .= ' '. t('The "Count by type" options will generate a link to show that type within that term.');
  }

  $form['count']['taxonomy_list_noshow'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#attributes' => array('class' => array('container-inline')),
    '#title' => t('Hide terms with no content?'),
    '#default_value' => (int) variable_get('taxonomy_list_noshow', FALSE),
    '#description' => t('Do not show the term if there is no content using the term. Requires one of the counting options above.'),
    );

  return system_settings_form($form);
}
