<?php

/**
 * @file
 * Common pages for the Media WYSIWYG module.
 */

/**
 * Form callback used when embedding media.
 *
 * Allows the user to pick a format for their media file.
 * Can also have additional params depending on the media type.
 */
function media_wysiwyg_format_form($form, &$form_state, $file) {
  $form_state['file'] = $file;

  // Allow for overrides to the fields.
  $query_fields = isset($_GET['fields']) ? drupal_json_decode($_GET['fields']) : array();
  $fields = media_wysiwyg_filter_field_parser(array('fields' => $query_fields), $file);

  $options = media_wysiwyg_get_file_view_mode_options($file);

  if (!count($options)) {
    throw new Exception('Unable to continue, no available formats for displaying media.');
  }

  // Generate all the previews.
  if (!isset($form_state['storage']['view_mode_previews'])) {
    $form_state['storage']['view_mode_previews'] = array();
    foreach ($options as $view_mode => $view_mode_label) {
      $view_mode_preview = media_wysiwyg_get_file_without_label($file, $view_mode, array('wysiwyg' => TRUE));
      $form_state['storage']['view_mode_previews'][$view_mode] = drupal_render($view_mode_preview);
    }
  }

  // Add the previews back into the form array so they can be altered.
  $form['#formats'] = &$form_state['storage']['view_mode_previews'];

  // Allow for overrides to the display format.
  $default_view_mode = is_array($query_fields) && isset($query_fields['format']) ? $query_fields['format'] : variable_get('media_wysiwyg_wysiwyg_default_view_mode', 'full');
  if (!isset($options[$default_view_mode])) {
    reset($options);
    $default_view_mode = key($options);
  }

  // Add the previews by reference so that they can easily be altered by
  // changing $form['#formats'].
  $settings['media']['formatFormFormats'] = &$form_state['storage']['view_mode_previews'];
  $form['#attached']['js'][] = array('data' => $settings, 'type' => 'setting');

  // Add the required libraries, JavaScript and CSS for the form.
  $form['#attached']['library'][] = array('media', 'media_base');
  $form['#attached']['library'][] = array('system', 'form');
  $form['#attached']['css'][] = drupal_get_path('module', 'media_wysiwyg') . '/css/media_wysiwyg.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'media_wysiwyg') . '/js/media_wysiwyg.format_form.js';

  $form['title'] = array(
    '#markup' => t('Embedding %filename', array('%filename' => $file->filename)),
  );

  $preview = media_get_thumbnail_preview($file);

  $form['preview'] = array(
    '#type' => 'markup',
    '#markup' => drupal_render($preview),
  );

  // These will get passed on to WYSIWYG.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('options'),
  );

  // @TODO: Display more verbose information about which formatter and what it
  // does.
  $form['options']['format'] = array(
    '#type' => 'select',
    '#title' => t('Display as'),
    '#options' => $options,
    '#default_value' => $default_view_mode,
    '#description' => t('Choose the type of display you would like for this
      file. Please be aware that files may display differently than they do when
      they are inserted into an editor.'),
  );

  // If necessary, display the alignment widget.
  if (variable_get('media_wysiwyg_alignment', FALSE)) {
    $align_default = empty($query_fields['alignment']) ? '' : $query_fields['alignment'];
    $align_options = array(
      '' => t('None'),
      'left' => t('Left'),
      'right' => t('Right'),
      'center' => t('Center'),
    );
    if (!isset($align_options[$align_default])) {
      // Safety code for a malformed token.
      $align_default = '';
    }
    $form['options']['alignment'] = array(
      '#type' => 'select',
      '#title' => t('Alignment'),
      '#options' => $align_options,
      '#description' => t('Choose how you would like the media to be aligned with surrounding content.'),
      '#default_value' => $align_default,
    );
  }
  // Add fields from the file, so that we can override them if necessary.
  $form['options']['fields'] = array();
  foreach ($fields as $field_name => $field_value) {
    $file->{$field_name} = $field_value;
  }
  // Get the external url from the fid array.
  $external_url = empty($query_fields['external_url']) ? NULL : $query_fields['external_url'];
  // Field to attach external url's to files for linking.
  if (variable_get('media_wysiwyg_external_link', FALSE)) {
    if ($file->type == 'image') {
      $form['options']['external_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Link Image'),
        '#description' => t('Enter a URL to turn the image into a link.'),
        '#default_value' => $external_url,
      );
    }
  }
  field_attach_form('file', $file, $form['options']['fields'], $form_state);
  $instance = field_info_instances('file', $file->type);
  foreach ($instance as $field_name => $field_value) {
    $info = field_info_field($field_name);
    $allow = !empty($instance[$field_name]['settings']['wysiwyg_override']);
    // Only single valued fields can be overridden normally, unless Media is
    // configured otherwise with "media_wysiwyg_wysiwyg_override_multivalue".
    if ($allow && $info['cardinality'] != 1) {
      $allow = variable_get('media_wysiwyg_wysiwyg_override_multivalue', FALSE);
    }
    $form['options']['fields'][$field_name]['#access'] = $allow;
  }

  // Add view mode preview.
  media_wysiwyg_format_form_view_mode($form, $form_state, $file);

  // Similar to a form_alter, but we want this to run first so that
  // media.types.inc can add the fields specific to a given type (like alt tags
  // on media). If implemented as an alter, this might not happen, making other
  // alters not be able to work on those fields.
  // @todo: We need to pass in existing values for those attributes.
  drupal_alter('media_wysiwyg_format_form_prepare', $form, $form_state, $file);

  if (!element_children($form['options'])) {
    $form['options']['#attributes'] = array('style' => 'display:none');
  }

  return $form;
}

/**
 * Add ajax preview when selecting view mode in wysiwyg editor.
 */
function media_wysiwyg_format_form_view_mode(&$form, $form_state, $file) {
  // Check to see if a view mode ("format") has already been specified for
  // this media item. First, check for a standard form-submitted value.
  if (!empty($form_state['values']['format'])) {
    $view_mode = $form_state['values']['format'];
  }
  // Second, check the request for a JSON-encoded value.
  elseif (isset($_GET['fields'])) {
    $query_fields = drupal_json_decode($_GET['fields']);
    if (isset($query_fields['format'])) {
      $view_mode = $query_fields['format'];
    }
  }
  // If we were unable to determine a view mode, or we found a view mode
  // that does not exist in the list of format options presented on this
  // form, use the default view mode.
  if (!isset($view_mode) || !array_key_exists($view_mode, $form['options']['format']['#options'])) {
    $view_mode = variable_get('media_wysiwyg_wysiwyg_default_view_mode', 'full');
  }

  $link_options = array(
    'attributes' => array(
      'class' => 'button',
      'title' => t('Use for replace fox or edit file fields.'),
    ),
    'query' => drupal_get_destination(),
  );
  if (!empty($_GET['render'])) {
    $link_options['query']['render'] = $_GET['render'];
  }

  $form['preview'] = array();
  $form['preview']['#prefix'] = '<div class="media-preview-group"><div class="media-item"><div class="media-thumbnail">';
  $form['preview']['#suffix'] = '</div><div class="label-wrapper"><label class="media-filename">' . check_plain($file->filename) . '</label></div></div><div class="edit-file-link">' . l(t('Edit file'), 'file/' . $file->fid . '/edit', $link_options) . '</div></div>';
  $form['preview']['thumbnail'] = file_view_file($file, $view_mode);
  $form['preview']['thumbnail']['#prefix'] = '<div id="media-preview">';
  $form['preview']['thumbnail']['#suffix'] = '</div>';

  if (!isset($form['options']['format']['#default_value'])) {
    $form['options']['format']['#default_value'] = $view_mode;
  }
  $form['options']['format']['#ajax'] = array(
    'callback' => 'media_wysiwyg_format_form_preview',
    'wrapper' => 'media-preview',
  );

  $wysiwyg_view_mode = db_query('SELECT view_mode FROM {media_view_mode_wysiwyg} WHERE type = :type', array(':type' => $file->type))->fetchField();
  $view_modes = media_wysiwyg_get_wysiwyg_allowed_view_modes($file);
  $formats = $options = array();

  foreach ($view_modes as $view_mode => $view_mode_info) {
    $options[$view_mode] = $view_mode_info['label'];

    if (!empty($wysiwyg_view_mode)) {
      $element = media_wysiwyg_get_file_without_label($file, $wysiwyg_view_mode, array('wysiwyg' => TRUE));
    }
    else {
      $element = media_wysiwyg_get_file_without_label($file, $view_mode, array('wysiwyg' => TRUE));
    }

    $formats[$view_mode] = drupal_render($element);
  }

  $form['#formats'] = $formats;
  $form['options']['format']['#options'] = $options;
}

/**
 * AJAX callback to select portion of format form to be updated with a preview.
 *
 * @param array $form
 *   An associative array containing the structure of the form.
 * @param array $form_state
 *   An associative array containing the current state of the form.
 *
 * @return array
 *   The preview form item.
 */
function media_wysiwyg_format_form_preview($form, $form_state) {
  return $form['preview']['thumbnail'];
}

/**
 * Upgrade a single media token to latest version.
 *
 * @param array $tag_info
 *   The media token as a json-decoded array.
 */
function media_wysiwyg_upgrade_token(array &$tag_info) {
  $version = variable_get('media_wysiwyg_token_version', '');
  if (version_compare($version, '3.0', '<')) {
    media_wysiwyg_aggregate_alignment($tag_info);
  }
  // Successive upgrades follows here.
}

/**
 * Upgrade media tokens in filtered text fields for a given entity.
 *
 * Only upgraded text fields will be updated in storage, omitting the costly
 * entity_save(). I.e. no new entity revisions.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int $id
 *   The entity ID to scan for media tokens in.
 *
 * @return array
 *   The number of found and upgraded tokens in entity, keyed by 'found' and
 *   'upgraded'.
 */
function media_wysiwyg_upgrade_entity_tokens($entity_type, $id) {
  $report = array(
    'found' => 0,
    'upgraded' => 0,
  );

  // Assert that the entity type has a valid controller class to avoid getting
  // php parse errors during token upgrades. See issue #2950150.
  $type_info = entity_get_info($entity_type);
  if (empty($type_info['controller class'])) {
    return $report;
  }
  if (!($entity = entity_load($entity_type, array($id)))) {
    return $report;
  };
  $entity = reset($entity);

  list(,, $bundle) = entity_extract_ids($entity_type, $entity);

  // Map between storage engines and the fields for it that will be updated.
  $storages = array();
  foreach (media_wysiwyg_filter_fields_with_text_filtering($entity_type, $entity) as $field_name) {
    $langcode = field_language($entity_type, $entity, $field_name);
    if (!isset($entity->{$field_name}[$langcode])) {
      continue;
    }
    $field = field_info_instance($entity_type, $field_name, $bundle);
    $field = field_info_field_by_id($field['field_id']);
    $field_id = $field['id'];
    foreach ($entity->{$field_name}[$langcode] as &$field_item) {
      if (empty($field_item['value'])) {
        continue;
      }
      preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $field_item['value'], $matches);
      foreach ($matches[0] as $tag_orig) {
        $tag_orig = str_replace(array('[[', ']]'), '', $tag_orig);
        $tag_info = drupal_json_decode($tag_orig);
        if (!isset($tag_info['type']) || $tag_info['type'] != 'media') {
          continue;
        }
        $report['found']++;
        // Perform the actual upgrade.
        media_wysiwyg_upgrade_token($tag_info);
        $tag_new = drupal_json_encode($tag_info);
        if (strcmp($tag_orig, $tag_new) == 0) {
          // No changes. Don't bother saving this.
          continue;
        }
        $report['upgraded']++;
        $tag_orig = '[[' . $tag_orig . ']]';
        $tag_new = '[[' . $tag_new . ']]';
        // The field_item is available by reference, so it will updated in the
        // entity directly. If several identical tokens exists within this text
        // value they will all be replaced here, and the next match iteration
        // will not perform any replacement as it the search string will not be
        // found. No big deal and no need to add a special case for this.
        $field_item['value'] = str_replace($tag_orig, $tag_new, $field_item['value']);
        $storages[$field['storage']['type']][$field_id] = $field_id;
      }
    }
  }
  // Write updated tokens to storage.
  foreach ($storages as $storage => $fields) {
    $storage_info = field_info_storage_types($storage);
    module_invoke($storage_info['module'], 'field_storage_write', $entity_type, $entity, FIELD_STORAGE_UPDATE, $fields);
  }
  return $report;
}

/**
 * Upgrade media tokens in content.
 *
 * Over time the format of media tokens will change and this function will
 * assert that existing tokens in content will remain up to date with todays
 * standard.
 *
 * It examines the {file_usage} table and searches all entities for filtered
 * text fields with macros. All found media tokens will be upgraded to the
 * latest token format version and the individual text fields will be updated in
 * db directly, omitting all hooks otherwise run during entity update.
 *
 */
function media_wysiwyg_upgrade_content_tokens() {
  $batch = array(
    'title' => t("Upgrading media tokens"),
    'operations' => array(
      array(
        'media_wysiwyg_upgrade_content_tokens_batch',
        array(),
      ),
    ),
    'finished' => 'media_wysiwyg_upgrade_content_tokens_finish',
    'file' => drupal_get_path('module', 'media_wysiwyg') . '/includes/media_wysiwyg.pages.inc',
  );
  batch_set($batch);
  batch_process('admin/reports/status');
}

/**
 * Batch API callback.
 *
 * @see media_wysiwyg_upgrade_content_tokens()
 */
function media_wysiwyg_upgrade_content_tokens_batch(&$context) {
  $items_per_run = 20;

  $query = db_select('file_managed', 'fm');
  $query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
  $query->fields('fu', array('type', 'id'))
    ->distinct();
  if (empty($context['results']['!entities_total'])) {
    // The countQuery() returns a cloned SelectQuery object, so we can happily
    // execute it without disturbing the original query. Also, the keys in the
    // 'results' entry are prefixed with '!' so the $results variable can be
    // sendt directly to t() in the batch finished callback.
    $context['results']['!entities_total'] = $query->countQuery()->execute()->fetchField();
    $context['results']['!entities_upgraded'] = 0;
    $context['results']['!tokens_total'] = 0;
    $context['results']['!tokens_upgraded'] = 0;

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_type'] = '';
    $context['sandbox']['current_id'] = 0;
    $context['sandbox']['run'] = 0;
  }
  $query->orderBy('fu.type')
    ->orderBy('fu.id')
    ->range($context['sandbox']['run'] * $items_per_run, $items_per_run);
  foreach ($query->execute() as $usage) {
    $context['sandbox']['progress']++;
    $context['sandbox']['current_id'] = $usage->id;
    $context['sandbox']['current_type'] = $usage->type;
    $context['message'] = t("Upgrading tokens: Processing entity # !progress/!total. Last examined: !entity_type/!entity_id", array(
      '!progress' => $context['sandbox']['progress'],
      '!total' => $context['results']['!entities_total'],
      '!entity_type' => $usage->type,
      '!entity_id' => $usage->id,
    ));
    try {
      $report = media_wysiwyg_upgrade_entity_tokens($usage->type, $usage->id);
    }
    catch (Exception $e) {
      watchdog('media', "Failed to upgrade tokens in entity %entity_id with id %entity_id", array('%entity_type' => $usage->type, '%entity_id' => $usage->id), WATCHDOG_WARNING);
    }
    $context['results']['!tokens_total'] += $report['found'];
    $context['results']['!tokens_upgraded'] += $report['upgraded'];
    if ($report['upgraded']) {
      $context['results']['!entities_upgraded']++;
    }
  }
  if ($context['sandbox']['progress'] < $context['results']['!entities_total']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['results']['!entities_total'];
  }
  $context['sandbox']['run']++;
}

/**
 * Batch API finish callback.
 *
 * @see media_wysiwyg_upgrade_content_tokens()
 */
function media_wysiwyg_upgrade_content_tokens_finish($success, $results, $operations) {
  if ($success) {
    $results['!version'] = MEDIA_WYSIWYG_TOKEN_VERSION;
    drupal_set_message(t("Media token version !version upgrade summary: <ul><li>Entities inspected: !entities_total</li> <li>Media tokens found: !tokens_total.</li> <li>Tokens upgraded: !tokens_upgraded</li> <li>Entities affected: !entities_upgraded</li></ul>", $results));
    variable_set('media_wysiwyg_token_version', MEDIA_WYSIWYG_TOKEN_VERSION);
    // Instead of using the costly drupal_flush_all_caches() we flush relevant
    // core caches and invoke hook_flush_caches() to allow content cache modules
    // (entitycache) to flush whatever needed.
    $core = array('cache', 'cache_filter', 'cache_page', 'cache_block');
    $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
    foreach ($cache_tables as $table) {
      cache_clear_all('*', $table, TRUE);
    }
  }
  else {
    drupal_set_message(t('Media token upgrade failed. See system log'), 'warning');
  }
}
