<?php
namespace KBOO\SpinUp;

class SeedTaxonomies {
  private $taxonomies = [];

  /**
   * Constructor
   */
  public function __construct()
  {
    $this->initialize();
    $this->execute();
  }

  /**
   * Initialize
   */
  private function initialize()
  {
    $this->taxonomies[] = [
      'act_types' => [
        'Music', /* 'Music' must always remain at this (0) index in the array
                  * due to default value set on field_act_type.
                 */
      ],
    ];

    $this->taxonomies[] = [
      'event_types' => [
        'Music',
        'Community',
      ],
    ];

    $this->taxonomies[] = [
      'organization_types' => [
        'Non-Profit',
        'Restaurant',
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
      'standalone_media_types' => [
        'Clip',
        'Full Episode',
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
  private function seed(array $vocabulary_definition)
  {
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
  private function hasTerm($term_name, $vocabulary_name)
  {
    $terms = taxonomy_get_term_by_name($term_name, $vocabulary_name);
    return (bool)count($terms);
  }

  /**
   * Execute the script
   */
  private function execute()
  {
    foreach ($this->taxonomies as $item) {
      $this->seed($item);
    }
  }
}

new SeedTaxonomies();
