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
      'field_topic_tags',
      5,
      'Taxonomy__topics_from_5'
    );

    $this->addTaxonomyMapping(
      'field_genres',
      2,
      'Taxonomy__genres_from_2'
    );

    parent::__construct($arguments);
  }
}
