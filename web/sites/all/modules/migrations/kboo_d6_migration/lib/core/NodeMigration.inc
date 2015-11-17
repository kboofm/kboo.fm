<?php
abstract class FileType {
  const FID = 'MigrateFileFid';
  const URI = 'MigrateFileUri';
  const URI_AS_IS = 'MigrateFileUriAsIs';
}

/**
 * Base class to support content type migrations.
 */
class NodeMigration extends DrupalNode6Migration {
  protected $exclude_source_nids;
  protected $source_nids;


  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addDependency('File');

    $this->addFieldMapping(
      'field_d6_nid',
      'nid'
    );

    $this->addFieldMapping(
      'title_field',
      NULL
    );

    parent::__construct($arguments);

    // Do not migrate the body summary
    $this->removeFieldMapping('body:summary');
  }


  /**
   * Append field value to the body field
   *
   * @param $row
   * @param $value
   */
  protected function appendBody($row, $value) {
    if (!empty($value)) {
      if (!empty($row->body)) {
        $row->body .= PHP_EOL;
      }
      $row->body .= $value;
    }
  }


  /**
   * Query
   *
   * @return \QueryConditionInterface
   */
  protected function query() {
    $query = parent::query();

    if (is_array($this->source_nids)) {
      $query->condition('n.nid', $this->source_nids, 'IN');
    }

    if (is_array($this->exclude_source_nids)) {
      $query->condition('n.nid', $this->exclude_source_nids, 'NOT IN');
    }

    return $query;
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

    // Set all rows to 'undefined' language
    $row->language = "";
    $row->title_field = $row->title;
    return TRUE;
  }


  /**
   * Add a migration dependencies
   *
   * @param $dependency
   */
  protected function addDependency($dependency) {
    $this->addDependencies([$dependency]);
  }


  /**
   * Add an array of migration dependencies
   *
   * @param array $dependencies
   */
  protected function addDependencies(array $dependencies) {
    if (!$this->dependencies) {
      $this->dependencies = [];
    }

    $this->dependencies = array_merge(
      $this->dependencies,
      $dependencies
    );
  }


  /**
   * Add field mapping for file types
   *
   * @param $d7
   * @param $src
   * @param string $type
   */
  protected function addFileMapping($d7, $src, $type = FileType::FID) {
    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration('File');

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue($type);

    if ($type == FileType::FID) {
      $mapping = $this->addFieldMapping("{$d7}:description");
      $mapping->defaultValue('');

      $mapping = $this->addFieldMapping("{$d7}:file_replace");
      $mapping->defaultValue(FILE_EXISTS_REPLACE);

      $mapping = $this->addFieldMapping("{$d7}:language");
      $mapping->defaultValue(LANGUAGE_NONE);

      $mapping = $this->addFieldMapping("{$d7}:preserve_files");
      $mapping->defaultValue(TRUE);
    }
  }


  /**
   * Add field mapping for external Uris
   *
   * @param $d7
   * @param $src
   * @param $base_url
   */
  protected function addExternalUriMapping($d7, $src, $base_url) {
    /*
     * NOTE: This doesn't actually work, leaving in repo in case need to return
     * to the idea later
     */
    $type = FileType::URI;

    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration('File');

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue($type);

    $mapping = $this->addFieldMapping("{$d7}:source_dir");
    $mapping->defaultValue($base_url);
  }


  /**
   * Add field mapping for uploads
   *
   * @param $d7
   */
  protected function addUploadMapping($d7) {
    $mapping = $this->addFieldMapping($d7, "upload");
    $mapping->sourceMigration('File');

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue(FileType::FID);

    $mapping = $this->addFieldMapping("{$d7}:description", "upload:description");
    $mapping->defaultValue('');

    $mapping = $this->addFieldMapping("{$d7}:preserve_files");
    $mapping->defaultValue(TRUE);

    $mapping = $this->addFieldMapping("{$d7}:language");
    $mapping->defaultValue(LANGUAGE_NONE);
  }


  /**
   * Add field mapping for image types
   *
   * @param $d7
   * @param $src
   */
  protected function addImageMapping($d7, $src) {
    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration('File');

    $this->addFieldMapping("{$d7}:alt", "{$src}:alt");
    $this->addFieldMapping("{$d7}:title", "{$src}:title");

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue(FileType::FID);

    $mapping = $this->addFieldMapping("{$d7}:preserve_files");
    $mapping->defaultValue(TRUE);
  }


  /**
   * Add field mapping for audio types
   *
   * @param $d7
   * @param $src
   */
  protected function addAudioMapping($d7, $src) {
    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration('File');

    $this->addFieldMapping("{$d7}:description", "{$src}:description");

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue(FileType::FID);

    $mapping = $this->addFieldMapping("{$d7}:preserve_files");
    $mapping->defaultValue(TRUE);
  }


  /**
   * Add field mapping for video types
   *
   * @param $d7
   * @param $src
   */
  protected function addVideoMapping($d7, $src) {
    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration('File');

    $mapping = $this->addFieldMapping("{$d7}:file_class");
    $mapping->defaultValue(FileType::URI);

    $this->addFieldMapping("{$d7}:description", "{$src}:description");
  }


  /**
   * Add field mapping for taxonomy types
   *
   * @param $d7
   * @param $source_vid
   * @param $source_migration
   */
  protected function addTaxonomyMapping($d7, $source_vid, $source_migration) {
    $mapping = $this->addFieldMapping($d7, $source_vid);
    $mapping->sourceMigration($source_migration);

    $mapping = $this->addFieldMapping("{$d7}:source_type");
    $mapping->defaultValue('tid');
  }


  /**
   * Translate an incoming D6 input format ID to D7 machine name
   *
   * @param $format
   * @return string|array
   */
  protected function mapFormat($format) {
    if (is_null($format)) {
      return 'filtered_html';
    }

    return parent::mapFormat($format);
  }


  /**
   * Add field mapping for a textarea field
   * @param $d7
   * @param $src
   */
  protected function addFormattedFieldMapping($d7, $src) {
    $this->addFieldMapping($d7, $src);

    $mapping = $this->addFieldMapping("{$d7}:format", "{$src}:format");
    $mapping->callbacks([$this, 'mapFormat']);
  }


  /**
   * Add field mapping for date types
   *
   * @param $d7
   * @param $src
   * @param bool|FALSE $to
   */
  protected function addDateMapping($d7, $src, $to = false) {
    $this->addFieldMapping($d7, $src);

    $mapping = $this->addFieldMapping("{$d7}:timezone");
    $mapping->defaultValue('America/Chicago');

    if ($to) {
      $this->addFieldMapping("{$d7}:to", "{$src}:value2");
    }
  }

  /**
   * Add field mapping for repeating date types
   *
   * @param $d7
   * @param $src
   */
  protected function addRepeatingDateMapping($d7, $src) {
    $this->addFieldMapping($d7, $src);

    $mapping = $this->addFieldMapping("{$d7}:timezone");
    $mapping->defaultValue('America/Chicago');

    $this->addFieldMapping("{$d7}:to", "{$src}:value2");
    $this->addFieldMapping("{$d7}:rrule", "{$src}:rrule");
  }


  /**
   * Add field mapping for reference types
   *
   * @param $d7
   * @param $src
   * @param $ref
   */
  protected function addReferenceMapping($d7, $src, $ref) {
    $mapping = $this->addFieldMapping($d7, $src);
    $mapping->sourceMigration($ref);
  }


  /**
   * Add field mapping for link types
   *
   * @param $d7
   * @param $src
   */
  protected function addLinkMapping($d7, $src) {
    $this->addFieldMapping($d7, $src);
    $this->addFieldMapping("{$d7}:attributes", "{$src}:attributes");
    $this->addFieldMapping("{$d7}:title", "{$src}:title");
  }


  /**
   * Add field mapping for address types
   *
   * @param $d7
   */
  protected function addAddressMapping($d7) {
    $this->addFieldMapping($d7, 'address_country');
    $this->addFieldMapping("{$d7}:name_line", "address_name");
    $this->addFieldMapping("{$d7}:thoroughfare", "address_street");
    $this->addFieldMapping("{$d7}:premise", "address_additional");
    $this->addFieldMapping("{$d7}:locality", "address_city");
    $this->addFieldMapping("{$d7}:administrative_area", "address_province");
    $this->addFieldMapping("{$d7}:postal_code", "address_postal_code");
  }


  /**
   * Remap D7 body from a different D6 field
   *
   * @param $src
   */
  protected function remapFromBodyMigration($src) {
    $this->removeFieldMapping('body', 'body');
    $this->addFieldMapping('body', $src);
  }


  /**
   * Set a field to a taxonomy term tid, and find the tid via term_name
   *
   * @param $node
   * @param $field_name
   * @param $vocabulary
   * @param $term_name
   */
  public function setTaxonomyTerm($node, $field_name, $vocabulary, $term_name) {
    static $data;

    if (!is_array($data)) {
      $data = [];
    }

    if (!$data[$field_name]) {
      $data[$field_name] = taxonomy_get_term_by_name(
        $term_name,
        $vocabulary
      );
    }

    $term = reset($data[$field_name]);
    $node->{$field_name}['und'][]['tid'] = $term->tid;
  }


  /**
   * Condition query to retrieve address data
   *
   * @param \QueryConditionInterface $query
   * @return \QueryConditionInterface
   */
  protected function addressQuery(QueryConditionInterface $query) {
    $fields = [
      'name',
      'street',
      'additional',
      'city',
      'province',
      'postal_code',
      'country',
    ];

    $fields = array_map(
      function ($field) {
        return [
          'fieldName' => $field,
          'fieldAlias' => "address_{$field}",
        ];
      },
      $fields
    );

    $query->leftJoin(
      'location_instance',
      'li',
      'li.nid = n.nid AND li.vid = n.vid'
    );

    $query->leftJoin(
      'location',
      'l',
      'l.lid = li.lid'
    );

    foreach ($fields as $field) {
      $query->addField(
        'l',
        $field['fieldName'],
        $field['fieldAlias']
      );
    }

    return $query;
  }
}
