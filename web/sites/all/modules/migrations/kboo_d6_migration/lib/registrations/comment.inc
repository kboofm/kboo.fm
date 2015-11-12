<?php

/**
 * Register the comment migrations
 */
class CommentRegistration extends BaseRegistration {

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
   * Configure the comment registration arguments
   *
   * @param $info
   */
  private function configureRegistration($info) {
    list($dest, $src, $node_migration) = $info;

    $this->custom_args = [
      'group_name' => 'Comments',
      'description' => t('Migration of comments from Drupal 6'),
      'class_name' => 'DrupalComment6Migration',
      'machine_name' => "Comment__{$dest}_from_{$src}",
      'description' => t("Migration of {$dest} comments from D6 vid {$src}"),
      'source_type' => $src,
      'destination_type' => $dest,
      'user_migration' => 'User',
      'node_migration' => $node_migration,
      'dependencies' => [
        'BasicPage_from_Page',
      ],
    ];
  }


  /**
   * Return a array map of D6 vid's to D7 machine_names
   *
   * @return array
   */
  public static function getMap() {
    /*
     * index 0 - D7 entity type machine name
     * index 1 - D6 content type machine name
     * index 2 - node_migration
     */

    return [
      [
        'basic_page',
        'page', // disabled
        'BasicPage_from_Page'
      ],

      [
        'blog_post',
        'blog',
        'BlogPost_from_Blog',
      ],

      [
        'book',
        'book',
        'Book_from_Book',
      ],

      [
        'organization',
        'sponsor', // disabled
        'Organization_from_Sponsor',
      ],

      [
        'program',
        'kboo_program',
        'Program_from_KbooProgram',
      ],

      [
        'station_content',
        'audio',
        'StationContent_from_Audio'
      ],

      [
        'station_content',
        'schedule_episode',
        'StationContent_from_ScheduleEpisode',
      ],
    ];
  }
}
