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

    $this->destination = new MigrateDestinationNode(
      'person_profile',
      $options
    );

    $this->map = new MigrateSQLMap(
      $this->machineName,
      $this->getSourceKey(),
      MigrateDestinationNode::getKeySchema()
    );
  }


  protected function mapFields() {
    $this->addFieldMapping(
      'title',
      'name'
    );

    $this->addFieldMapping(
      'title_field',
      'name'
    );

    $this->addFieldMapping(
      'body',
      'body'
    );

    $this->addFieldMapping(
      'field_profile_type',
      'profile_type'
    );
  }


  protected function buildQuery() {
   $user_fields = [
     'uid',
     'name',
    ];

    $connection = Database::getConnection('default', 'legacy');

    // Active users, excluding anonymous
    $query = $connection->select('users', 'u');
    $query->fields('u', $user_fields);
    $query->condition('u.status', 1, '=');
    $query->condition('u.uid', 0, '>');

    // Get profile body value
    $query->leftJoin(
      'profile_values',
      'pv',
      'pv.uid = u.uid AND pv.fid = 14'
    );
    $query->addField('pv', 'value', 'body');

    // Ensure user is a show host
    $role_id = 12; // "author - program"
    $query->join('users_roles', 'ur', 'u.uid = ur.uid');
    $query->condition('ur.rid', $role_id, '=');
    return $query;
  }


  protected function getSourceKey() {
    return [
      'uid' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ],
    ];
  }


  /**
   * Prepare the destination node
   *
   * @param $node
   * @param $row
   */
  public function prepare($node, $row) {
    static $term;

    if (!$term) {
      $terms = taxonomy_get_term_by_name(
        'Show Host',
        'profile_types'
      );
      $term = reset($terms);
    }

    $node->field_profile_type['und'][]['tid'] = $term->tid;
  }
}
