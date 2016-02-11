<?php
namespace KBOO\SpinUp;

class SeedTaxonomies {
  private $taxonomies = [];

  /**
   * Constructor
   */
  public function __construct() {
    $this->initialize();
    $this->execute();
  }

  /**
   * Initialize
   */
  private function initialize() {
    $this->taxonomies[] = [
      'event_types' => [
        'Community events',
        'KBOO events',
        'Concerts',
        'Art and culture',
      ],
    ];

    $this->taxonomies[] = [
      'organization_types' => [
        'Non-Profit',
        'Restaurant',
        'Sponsor',
        'Venue',
      ],
    ];

    $this->taxonomies[] = [
      'profile_types' => [
        'Author',
        'Show Host',
        'Staff',
      ],
    ];

    $this->taxonomies[] = [
      'program_types' => [
        'Channel/Stream',
        'Membership',
        'Show',
      ],
    ];

    $this->taxonomies[] = [
      'station_content_types' => [
        'Clip',
        'Episode',
        'Newsletter',
        'Release',
      ],
    ];
  }

  /**
   * Seed a taxonomy vocabulary and terms
   *
   * @param array $vocabulary_definition
   */
  private function seed(array $vocabulary_definition) {
    $vocabulary_name = key($vocabulary_definition);
    $term_names = reset($vocabulary_definition);
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);

    if (!$vocabulary) {
      echo "Vocabulary {$vocabulary_name} not found" . PHP_EOL;
      return;
    }

    foreach ($term_names as $term_name) {
      if ($this->hasTerm($term_name, $vocabulary_name)) {
        continue;
      }

      $term = new \stdClass();
      $term->name = $term_name;
      $term->vid = $vocabulary->vid;
      taxonomy_term_save($term);

      echo "Added {$vocabulary_name}: {$term_name}" . PHP_EOL;
    }
  }

  /**
   * Check if the taxonomy term already exists.
   *
   * @param $term_name
   * @param $vocabulary_name
   * @return bool
   */
  private function hasTerm($term_name, $vocabulary_name) {
    $terms = taxonomy_get_term_by_name($term_name, $vocabulary_name);
    return (bool)count($terms);
  }

  /**
   * Execute the script
   */
  private function execute() {
    foreach ($this->taxonomies as $item) {
      $this->seed($item);
    }
  }
}

new SeedTaxonomies();
