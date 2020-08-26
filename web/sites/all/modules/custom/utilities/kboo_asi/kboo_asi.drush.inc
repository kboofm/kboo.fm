<?php

/**
 * Implements hook_drush_command().
 */
function kboo_asi_drush_command() {
  $examples = [
    'get-as-db' => [
      'key' => 'drush get-as-db',
      'value' => 'Retrieves most recent archive space db from the ftp server',
    ],

    'import-as-db' => [
      'key' => 'drush import-as-db',
      'value' => 'Imports most recently downloaded archive space db into the working database',
    ],

    'check-as-db' => [
      'key' => 'drush check-as-db',
      'value' => 'Checks working db for new recordings and creates drupal nodes',
    ],
  ];

  $items['get-as-db'] = [
    'description' => 'Retrieve archivespace database from FTP server',
    'aliases' => ['gasdb'],
  ];

/*
  $items['schedule-cache-clear'] = [
    'description' => 'Clear the schedule cache for the given weeks',
    'aliases' => ['sch-cc'],
    'options' => [
      'min' => 'Minimum week',
      'max' => 'Maximum week',
    ],
    'examples' => [
      $examples['clear']['key'] => $examples['clear']['value'],
    ],
  ];
*/

  $items['import-as-db'] = [
    'description' => 'Import archivespace database to working database',
    'aliases' => ['iasdb'],
  ];

  $items['check-as-db'] = [
    'description' => 'Checks current working db against existing nodes; creates/imports new nodes if necessary',
    'aliases' => ['casdb'],
  ];
  return $items;
}


function drush_kboo_asi_get_as_db()
{
	return kboo_asi_get_as_db(TRUE);
}

function drush_kboo_asi_import_as_db()
{
	return kboo_asi_import_as_db(TRUE);
}

function drush_kboo_asi_check_as_db()
{
	//
#ftp_getter_template is the ftp template
}

