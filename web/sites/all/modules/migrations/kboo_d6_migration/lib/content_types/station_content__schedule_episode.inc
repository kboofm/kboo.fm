<?php


/**
 * Migrates D7 station_content from D6 schedule_episode.
 */
class StationContentFromScheduleEpisode extends NodeMigration {

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

    $this->addRepeatingDateMapping(
      'field_air_time',
      'field_schedule_date'
    );

    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

    $this->addImageMapping(
      'field_lead_image',
      'lead_image'
    );

    $this->addImageMapping(
      'field_more_images',
      'field_node_image'
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

    $row->lead_image = array_shift($row->field_node_image);
    return TRUE;
  }
}
