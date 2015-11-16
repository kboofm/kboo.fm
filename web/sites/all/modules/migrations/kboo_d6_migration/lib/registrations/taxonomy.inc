<?php

/**
 * Register the taxonomy migrations
 */
class TaxonomyRegistration extends BaseRegistration {

  /**
   * Constructor
   *
   * @param $info
   */
  public function __construct($info) {
    parent::__construct();
    $this->configureRegistration($info);
  }

  /**
   * Configure the taxonomy registration arguments
   *
   * @param $info
   */
  private function configureRegistration($info) {
    list($dest, $src) = $info;

    $this->custom_args = [
      'group_name' => 'Taxonomy',
      'class_name' => 'DrupalTerm6Migration',
      'source_vocabulary' => $src,
      'destination_vocabulary' => $dest,
      'machine_name' => "Vocabulary__{$dest}_from_{$src}",
      'description' => t("Migration of {$dest} vocabulary from D6 vid {$src}"),
    ];
  }


  /**
   * Return a array map of D6 vid's to D7 machine_names
   *
   * @return array
   */
  public static function getMap() {
    /*
     * index 0 - D7 machine_name
     * index 1 - D6 vid
     */
    return [
      [
        'genres',
        '2', // Music genres
      ],

      [
        'topics',
        '5', // Public affairs topics
      ],

      [
        'topics',
        '12', // Blogs
      ],
    ];
  }
}
