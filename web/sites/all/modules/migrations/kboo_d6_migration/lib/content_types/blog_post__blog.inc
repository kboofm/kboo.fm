<?php


/**
 * Migrates D7 blog_post from D6 blog.
 */
class BlogPostFromBlog extends NodeImageMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

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

//    $this->addTaxonomyMapping(
//      'field_topic_tags',
//      12, // D6: Blogs
//      'Vocabulary__topics_from_5'
//    );

    parent::__construct($arguments);
  }
}
