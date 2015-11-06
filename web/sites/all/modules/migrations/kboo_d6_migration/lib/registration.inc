<?php

/**
 * Register all D6 -> D7 Migrations
 */
class KBOOMigrationRegistration {

  /**
   * Register the migrations
   */
  public static function register() {
    UserPictureRegistration::register();
    RoleRegistration::register();
    UserRegistration::register();
  }
}
