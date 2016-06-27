# Updating Drupal Core

Open composer.json and set "drupal/drupal" to the target version.

$ composer up
$ git apply -v patches/core/delete-robots-txt.patch
$ drush updatedb
$ drush cc all

## Creating a patch


$ git format-patch -M b3a2ea5df54d0b6ec978b63892be8bfdbf749fd5

This creates a file like delete-robots-txt.patch
