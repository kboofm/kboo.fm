<?php


/**
 * Migrates D7 program from D6 kboo_program.
 */
class ProgramFromKbooProgram extends NodeMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addDependencies([
      'PersonProfile_from_UserProfile',
    ]);

    $this->addReferenceMapping(
      'field_hosted_by',
      'field_program_host',
      'PersonProfile_from_UserProfile'
    );

    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

    $this->addLinkMapping(
      'field_links',
      'field_kboo_program_link'
    );

    $this->addImageMapping(
      'field_lead_image',
      'lead_image'
    );

    $this->addImageMapping(
      'field_more_images',
      'field_node_image'
    );

    $this->addFieldMapping(
      'field_episode_record',
      'field_episode_record'
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
