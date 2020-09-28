<?php
/**
 * @file
 * Support for migration into Name fields.
 */

/**
 * Allows using Name fields as Migrate destinations.
 *
 * The primary value passed to this field handler must be the 'given' component.
 *
 * Example usage:
 * @code
 *   // The given component should be mapped as the primary value.
 *   $this->addFieldMapping('field_name', 'profile_first_name');
 *   // Now map other name components.
 *   $this->addFieldMapping('field_name:title', 'profile_title');
 *   $this->addFieldMapping('field_name:middle', 'profile_middle_name');
 *   $this->addFieldMapping('field_name:family', 'profile_last_name');
 * @endcode
 *
 * @see MigrateDefaultFieldHandler
 */
class MigrateNameHandler extends MigrateFieldHandler {
  protected $primaryColumn = 'given';

  /**
   * Declares the types of fields used.
   */
  public function __construct() {
    $this->registerTypes(array('name'));
  }

  /**
   * Implements MigrateFieldHandler::fields().
   *
   * Returns all available fields except for 'given',
   * which is the primary column.
   *
   * @param string $field_type
   *   The field type.
   * @param array $field_instance
   *   The field instance.
   *
   * @return array
   *   The available fields.
   */
  public function fields($field_type, $field_instance) {
    $field_info = field_info_field($field_instance['field_name']);
    $fields = array();
    foreach ($field_info['columns'] as $column_name => $column_info) {
      // The first column is the primary value, which is mapped directly to
      // the field name - so, don't include it here among the subfields.
      if ($column_name != $this->primaryColumn) {
        $fields[$column_name] = empty($column_info['description']) ?
          $column_name : $column_info['description'];
      }
    }
    return $fields;
  }

  /**
   * Implements MigrateFieldHandler::prepare().
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    // Get arguments, if any.
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }

    // Get language.
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Get name-specific field settings.
    $components = array_filter($field_info['settings']['components']);

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      // Handle multivalue arguments (especially for subfields).
      $delta_arguments = array();
      foreach ($arguments as $name => $argument) {
        if (is_array($argument) && isset($argument[$delta])) {
          $delta_arguments[$name] = $argument[$delta];
        }
        else {
          $delta_arguments[$name] = $argument;
        }
      }
      $item = array($this->primaryColumn => $value) + array_intersect_key($delta_arguments, $field_info['columns']);
      $item = array_intersect_key($item, $components);
      if (array_filter($item)) {
        $return[$language][] = $item;
      }
      $delta++;
    }

    return isset($return[$language]) ? $return : NULL;
  }
}
