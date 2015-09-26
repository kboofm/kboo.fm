<?php

class BlogPostContentType {
  /**
   * Check if the blog_post node author is a show host
   *
   * @param $node
   * @return bool
   *
   */
  public static function isAuthorShowHost($node) {
    $terms = taxonomy_get_term_by_name('Show Host', 'profile_types');
    $termShowHost = reset($terms);

    if (!isset($node->field_authored_by['und'][0]['target_id'])) {
      return FALSE;
    }

    $author = node_load($node->field_authored_by['und'][0]['target_id']);

    if (!$author) {
      return FALSE;
    }

    $author_tids = array_map(
      function ($profile_types) {
        return $profile_types['tid'];
      },
      $author->field_profile_type['und']
    );

    return in_array($termShowHost->tid, $author_tids);
  }
}
