<?php

class UserProfileMigration extends Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->defineMigration();
    $this->mapFields();
  }


  protected function defineMigration() {
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
  }


  protected function mapFields() {
    $this->addFieldMapping(
      'title',
      'title'
    );

    $this->addFieldMapping(
      'title_field',
      NULL
    );

    $this->addFieldMapping(
      'field_profile_type',
      'profile_type'
    );
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
    $query->condition('u.uid', 0, '>');

    // Ensure user is a show host
    $role_id = 12; // "author - program"
    $query->join('users_roles', 'ur', 'u.uid = ur.uid');
    $query->condition('ur.rid', $role_id, '=');

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
        'Show Host',
        'profile_types'
      );
      $term = reset($terms);
    }

    $row->profile_type = $term->tid;
    $row->title_field = $row->title;
    return TRUE;
  }
}
