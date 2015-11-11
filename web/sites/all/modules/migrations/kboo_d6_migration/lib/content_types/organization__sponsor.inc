<?php


/**
 * Migrates D7 organization from D6 sponsor.
 */
class OrganizationFromSponsor extends NodeMigration {

  /**
   * Constructor
   *
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->addFieldMapping(
      "field_location:thoroughfare",
      "field_address"
    );

    $this->addFieldMapping(
      "field_location:locality",
      "field_city"
    );

    $this->addFieldMapping(
      "field_location:administrative_area",
      "field_state"
    );

    $this->addFieldMapping(
      "field_location:postal_code",
      "field_zipcode"
    );

    $this->addFieldMapping(
      'field_phone',
      'field_phone'
    );

    $this->addFieldMapping(
      'field_url',
      'field_website_url'
    );

    parent::__construct($arguments);
  }
}
