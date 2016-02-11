<?php

class RadioAutoComplete {

  /**
   * Get autocomplete definitions
   *
   * @return null|string
   */
  public static function getAutocompleteInfo() {
    $fields = [
      'field_person_profile' => [
        'program',
      ],

      'field_related_show_host' => [
        'basic_page',
        'blog_post',
        'book',
        'event',
        'organization',
        'person_profile',
        'program',
        'station_content',
      ],

      'field_show' => [
        'scheduled_timeslot',
      ],

      'field_stream' => [
        'scheduled_timeslot',
      ],

      'field_streams' => [
        'program',
      ],

      'field_venue' => [
        'event',
      ],
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
    $query = new ProgramQuery();
    $query->getStreams();
    $query->searchTitle($string, EStringSearchOptions::StartsWith);
    $query->setLimit(10);
    return static::getMatchResults($query, 'title_field');
  }


  /**
   * Fuzzy search for program shows
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchProgramShows($string) {
    $query = new ProgramQuery();
    $query->getShows();
    $query->searchTitle($string, EStringSearchOptions::StartsWith);
    $query->setLimit(10);
    return static::getMatchResults($query, 'title_field');
  }


  /**
   * Fuzzy search for person_profile show hosts
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchPersonProfileShowHosts($string) {
    $query = new PersonProfileQuery();
    $query->getShowHosts(EShowHostStatus::Active);
    $query->searchTitle($string, EStringSearchOptions::StartsWith);
    $query->setLimit(10);
    return static::getMatchResults($query, 'title_field');
  }


  /**
   * Fuzzy search for organization venues
   *
   * @param $string
   * @return array
   */
  public static function fuzzyMatchOrganizationVenues($string) {
    $query = new OrganizationQuery();
    $query->getVenues($string);
    $query->searchTitle($string, EStringSearchOptions::StartsWith);
    $query->setLimit(10);
    return static::getMatchResults($query, 'title_field');
  }
}
