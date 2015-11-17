<?php


/**
 * Migrates D7 basic_page from D6 page.
 */
class BasicPageFromPage extends NodeImageMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addTaxonomyMapping(
      'field_genres',
      2, // D6: Music genres
      'Vocabulary__genres_from_2'
    );

    $this->addTaxonomyMapping(
      'field_topic_tags',
      5, // D6: Public affairs topics
      'Vocabulary__topics_from_5'
    );

    parent::__construct($arguments);
  }
}
