<?php

class UserProfileMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $query = $this->buildQuery();
    $this->source = new MigrateSourceSQL($query);
    $this->source->setMapJoinable(false);

    $options = [
      'text_format' => 'filtered_html',
    ];

    $this->destination = new MigrateDestinationNode('person_profile', $options);
    $this->map = new MigrateSQLMap(
      $this->machineName,
      $this->getSourceKey(),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('title', 'title');
  }


  protected function buildQuery() {
    $fields = [
      'fid',
      'uid',
      'value',
    ];

    $connection = Database::getConnection('default', 'legacy');
    $query = $connection->select('profile_values', 'pv');
    $query->join('users', 'u', 'u.uid = pv.uid');
    $query->condition('u.status', 1, '=');
    $query->fields('pv', $fields);
    return $query;
  }


  protected function getSourceKey() {
    return [
      'fid' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ],
      'uid' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ],
    ];
  }
}
