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

    $this->addAudioMapping(
      'field_audio_files',
      'field_episode_audio'
    );

    $this->addFieldMapping(
      'field_episode_record',
      'field_episode_record'
    );

    $this->addFieldMapping(
      'migrate_redirects',
      'path'
    );

    parent::__construct($arguments);
  }
}
