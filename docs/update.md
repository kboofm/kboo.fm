# Updating Drupal Core

Open composer.json and set "drupal/drupal" to the target version.

$ composer up

Each time you update the Drupal Core you need to apply this robot.txt patch.

$ git apply -v patches/core/delete-robots-txt.patch
$ drush updatedb
$ drush cc all

## Creating a patch

$ git format-patch -M b3a2ea5df54d0b6ec978b63892be8bfdbf749fd5

This creates a file like delete-robots-txt.patch

## About Robots.text

The default robots.txt file has been intentionally deleted. Support for robots.txt is provided by the radio_station module.

See Updating Drupal core for applying the patch that deletes the default robots.txt file.

By default the following content will be served for robots.txt

```
User-agent: *
Disallow: /
```

The following instructions explain how to override this for production.

Create the gitignored file with the following content
web/sites/all/modules/custom/utilities/radio_station/lib/configs/.env
```
prod
```

The content for the .env file informs which robots file to load and serve. By setting .env to "prod" the contents of following file will be served
web/sites/all/modules/custom/utilities/radio_station/robots/prod.txt


Note: The above file is not gitignored. However, as stated above, the .env file is gitignored. The .env file is not actually required. If it does not exist then the default robots.txt content will be served.
