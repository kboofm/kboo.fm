<?php


/**
 * Migrates D7 program from D6 kboo_program.
 */
class ProgramFromKbooProgram extends NodeImageMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
//    $this->addDependencies([
//      'UserProfileMigration',
//    ]);

//    $this->addReferenceMapping(
//      'field_hosted_by',
//      'field_program_host',
//      'UserProfileMigration'
//    );

    $this->addFieldMapping(
      'field_short_description',
      'field_short_description'
    );

    $this->addLinkMapping(
      'field_links',
      'field_kboo_program_link'
    );

    $this->addFieldMapping(
      'field_episode_record',
      'field_episode_record'
    );

    parent::__construct($arguments);
  }
}
