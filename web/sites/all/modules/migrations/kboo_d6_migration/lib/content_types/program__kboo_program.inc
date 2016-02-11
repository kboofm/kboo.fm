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
    $this->addDependencies([
      'UserProfile',
    ]);

    $this->addReferenceMapping(
      'field_hosted_by',
      'field_program_host',
      'UserProfile'
    );

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

    $this->addFieldMapping(
      'migrate_redirects',
      'path'
    );

    parent::__construct($arguments);
  }
}
