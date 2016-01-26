<?php

class CapitalizeLocationCountry {

  /**
   * Execute the script
   */
  public function execute() {
    db_update("field_data_field_location")
      ->fields(["field_location_country" => "US",])
      ->execute();

    echo PHP_EOL;
    echo PHP_EOL;
  }
}


$script = new CapitalizeLocationCountry();
$script->execute();
