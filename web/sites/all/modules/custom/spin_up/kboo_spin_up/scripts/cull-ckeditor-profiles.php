<?php
namespace KBOO\SpinUp;

class CullCkeditorProfiles {

  /**
   * Constructor
   */
  public function __construct() {
    $this->ckeditor_profile_delete('Advanced');
    $this->ckeditor_profile_delete('Full');
  }


  /**
   * Copied from: web/sites/all/modules/contrib/ckeditor/includes/ckeditor.admin.inc
   *
   * @param $name
   */
  private function ckeditor_profile_delete($name) {
    db_delete('ckeditor_settings')
      ->condition('name', $name)
      ->execute();

    db_delete('ckeditor_input_format')
      ->condition('name', $name)
      ->execute();
  }
}

new CullCkeditorProfiles();
