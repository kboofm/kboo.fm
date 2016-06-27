# Site Install

## Requirements

- Mysql
- composer
- drush
- PHP
- PHP5-fpm
- Apache2
- MariaDB

## Install Drupal

Install Drupal using "Minimal Install" profile. For that you have to create database, configure the site with the web server and install Drupal via the install url.

```
drush en -y environment_setup_dev
# The "theme" feature is not turning on the frontend theme as expected.
drush en -y kbooui
drush vset theme_default kbooui
drush vset site_frontpage home
# The "configure_admin_ui" feature is not enabling the admin theme as
expected.
drush en -y adminimal
# Some features have to be reverted from the outset.
drush features-revert-all -y --force
# Note, when running locally adjust the path to your local docroot.
drush scr
/home/sandbox/drupal-composer/kboo/web/sites/all/modules/custom/spin_up/kb
oo_spin_up/scripts/seed-taxonomies.php
drush scr
/home/sandbox/drupal-composer/kboo/web/sites/all/modules/custom/spin_up/kb
oo_spin_up/scripts/cull-ckeditor-profiles.php
drush scr
/home/sandbox/drupal-composer/kboo/web/sites/all/modules/custom/spin_up/kb
oo_spin_up/scripts/default-variables.php
# Clear cache
drush cc all
```

You will also need to update dependencies through [composer](http://getcomposer.org):

```
composer up
```
