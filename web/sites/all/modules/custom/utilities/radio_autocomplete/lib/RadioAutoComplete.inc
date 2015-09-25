<?php

class RadioAutoComplete {

  /**
   * Get autocomplete definitions
   *
   * @return null|string
   */
  public static function getAutocompleteInfo() {
    $all_types = [
      'act',
      'article',
      'basic_page',
      'blog_post',
      'event',
      'image_gallery',
      'organization',
      'person_profile',
      'program',
      'standalone_media',
    ];

    $fields = [
      'field_person_profile' => [
        'program',
      ],

      'field_program' => [
        'person_profile',
        'program',
      ],

      'field_related_show_hosts' => $all_types,
      'field_related_organizations' => $all_types,
    ];

    $definitions = [];
    foreach ($fields as $name => $types) {
      $definitions[$name] = [
        'field' => $name,
        'callback' => "radio_autocomplete_{$name}",
        'uri' => "callbacks/autocomplete/{$name}",
        'types' => $types,
      ];
    }

    return $definitions;
  }


  /**
   * Build callback routes array for hook_menu
   *
   * @return array
   */
  public static function buildRoutes() {
    $items = [];

    foreach (RadioAutoComplete::getAutocompleteInfo() as $info) {
      $info = (object)$info;

      $items[$info->uri] = array(
        'page callback' => $info->callback,
        'access arguments' => array('access user profiles'),
        'type' => MENU_CALLBACK
      );
    }

    return $items;
  }


  /**
   * Build matches array from query results
   *
   * @param $query
   * @param $field_name
   * @return array
   */
  protected static function getMatchResults($query, $field_name) {
    $result = $query->execute();

    $entities = $result['node'];
    field_attach_load(
      'node',
      $entities,
      FIELD_LOAD_CURRENT
    );

    $matches = [];
    foreach ($entities as $entity) {
      $field = field_get_items('node', $entity, $field_name);
      $value = $field[0]['value'];

      $key = "{$value} ({$entity->nid})";
      $matches[$key] = "<div class=\"reference-autocomplete\">{$value}</div>";
    }

    return $matches;
  }


  public static function attach(&$form) {
    if (!isset($form['#node'])) {
      return;
    }

    $type = $form['#node']->type;

    foreach (RadioAutoComplete::getAutocompleteInfo() as $info) {
      $info = (object)$info;

      if (!in_array($type, $info->types)) {
        continue;
      }

      static::attachAutocompleteInfo($form, $info);
    }
  }

  /**
   * Attach an autocomplete info to the form
   *
   * @param $form
   * @param $info
   */
  public static function attachAutocompleteInfo(&$form, $info) {
    $field = $info->field;

    if (!isset($form[$field])) {
      return;
    }

    // Attach a custom autocomplete path
    foreach ($form[$field]['und'] as $delta => $element) {
      if (!is_numeric($delta)) {
        continue;
      }

      $form[$field]['und'][$delta]['target_id']['#autocomplete_path'] = $info->uri;
    }
  }


  /**
   * Fuzzy search for program streams
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchProgramStreams($string) {
    $query = new ProgramFieldQuery();
    $query->getStreams($string);
    return static::getMatchResults($query, 'title_field');
  }


  /**
   * Fuzzy search for person_profile show hosts
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchPersonProfileShowHosts($string) {
    $query = new PersonProfileFieldQuery();
    $query->getShowHosts($string);
    return static::getMatchResults($query, 'title_field');
  }


  /**
   * Fuzzy search for organization venues
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchOrganizationVenues($string) {
    $query = new OrganizationFieldQuery();
    $query->getVenues($string);
    return static::getMatchResults($query, 'title_field');
  }
}
