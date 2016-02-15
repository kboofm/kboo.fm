<?php


/**
 * Migrates D7 station_content from D6 audio.
 */
class StationContentFromAudio extends NodeMigration {

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
      'field_program',
      'Program_from_KbooProgram'
    );

    $this->addDateMapping(
      'field_air_time',
      'field_air_date'
    );

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

    $this->addFieldMapping(
      'migrate_redirects',
      'path'
    );

    $this->addAudio();

    parent::__construct($arguments);
  }


  private function addAudio() {
    $d7 = "field_audio_files";

    $mapping = $this->addFieldMapping(
      $d7,
      'audio_fid'
    );
    $mapping->sourceMigration('File');

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue(FileType::FID);

    $mapping = $this->addFieldMapping("{$d7}:preserve_files");
    $mapping->defaultValue(TRUE);
  }


  /**
   * Query
   *
   * @return \QueryConditionInterface
   */
  protected function query() {
    $query = parent::query();

    $query->leftJoin(
      'audio',
      'au',
      'au.nid = n.nid AND au.vid = n.vid'
    );

    $query->addField(
      'au',
      'fid',
      'audio_fid'
    );

    return $query;
  }
}
