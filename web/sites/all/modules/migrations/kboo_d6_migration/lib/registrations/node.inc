<?php

/**
 * Register a Node migration
 */
class NodeRegistration extends BaseRegistration {
  private $format_mappings;


  /**
   * Constructor
   *
   * @param $info
   */
  public function __construct($info) {
    parent::__construct();
    $this->defineFormatMappings();
    $this->configureRegistration($info);
  }


  /**
   * Define the D6 to D7 map for input formats
   */
  private function defineFormatMappings()
  {
    /*
     * key = D6 id
     * value = D7 name
     * comment = D6 name
     */
    $this->format_mappings = [
      '1' => 'filtered_html',             // Filtered HTML
      '2' => NULL,                        // PHP Code
      '3' => 'full_html',                 // Full HTML + advanced WYSIWYG
      '4' => 'full_html_no_wysiwyg',      // Full HTML + keep WYSIWYG off
    ];
  }


  /**
   * Parse to proper name
   *
   * @param $source Example value: basic_page
   * @return string Example value: BasicPage
   */
  private function parseToProperName($source) {
    $proper = array_map(
      'ucwords',
      explode('_', $source)
    );
    return join('', $proper);
  }


  /**
   * Configure the node registration arguments
   *
   * @param $info
   */
  private function configureRegistration($info) {
    list($d7['source'], $d6['source']) = $info;
    $d6['proper'] = $this->parseToProperName($d6['source']);
    $d7['proper'] = $this->parseToProperName($d7['source']);

    // Example: BasicPageFromPage
    $class_name = $d7['proper'] . 'From' . $d6['proper'];

    // Example: Migration of D7 basic_page nodes from D6 page
    $description = 'Migration of D7 ' . $d7['source'] . ' nodes from D6 ' . $d6['source'];

    // Example: BasicPage_from_Page
    $machine_name = $d7['proper'] . '_from_' . $d6['proper'];

    /*
     * A bit of a hack to get Events into it's own group. Doing this to
     * separate events for testing b/c there are so many nodes
     */
    $group_name = 'Content Types';
//    if ($machine_name == 'Event_from_Events') {
//      $group_name = 'Events';
//    }

    $this->custom_args = [
      'group_name' => $group_name,
      'user_migration' => 'User',
      'default_uid' => 1,
      'class_name' => $class_name,
      'description' => $description,
      'machine_name' => $machine_name,
      'source_type' => $d6['source'],
      'destination_type' => $d7['source'],
      'format_mappings' => $this->format_mappings,
    ];
  }


  /**
   * Return a array map of content type migration args
   *
   * @return array
   */
  public static function getMap() {
    // Get a list of content type migrations
    $path = dirname(__DIR__) . "/content_types";
    $map = array_values(
      array_filter(
        scandir($path),
        function ($filename) use ($path) {
          return !is_dir("{$path}/{$filename}");
        }
      )
    );

    // Strip file extension,
    // then explode filename into d7 and d6 content type name
    $map = array_map(
      function ($filename) use ($path) {
        $pathinfo = pathinfo($path . '/' .$filename);
        return explode('__', $pathinfo['filename']);
      },
      $map
    );

    return $map;
  }
}
