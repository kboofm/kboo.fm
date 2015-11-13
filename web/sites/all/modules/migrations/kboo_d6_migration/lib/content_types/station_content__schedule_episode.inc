<?php


/**
 * Migrates D7 station_content from D6 schedule_episode.
 */
class StationContentFromScheduleEpisode extends NodeImageMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addDependencies([
      'Program_from_KbooProgram',
    ]);

    $this->addReferenceMapping(
      'field_produced_for',
      'field_schedule_program',
      'Program_from_KbooProgram'
    );

    $this->addDateMapping(
      'field_air_time',
      'field_schedule_date',
      TRUE
    );

    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

    $this->addFieldMapping(
      'field_station_content_type',
      'station_content_type'
    );

    parent::__construct($arguments);
  }


  /**
   * Prepare the source row
   *
   * @param $row
   * @return bool
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    static $term;
    if (!$term) {
      $terms = taxonomy_get_term_by_name(
        $this->profile_type_taxonomy_name,
        'profile_types'
      );
      $term = reset($terms);
    }

    $row->station_content_type = $term->tid;
    return TRUE;
  }
}