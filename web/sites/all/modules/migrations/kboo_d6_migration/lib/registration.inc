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
    FileRegistration::register();
    UserProfileRegistration::register();

    foreach (TaxonomyRegistration::getMap() as $info) {
      TaxonomyRegistration::register($info);
    }

    foreach (NodeRegistration::getMap() as $info) {
      NodeRegistration::register($info);
    }

//    foreach (CommentRegistration::getMap() as $info) {
//      CommentRegistration::register($info);
//    }
  }
}
