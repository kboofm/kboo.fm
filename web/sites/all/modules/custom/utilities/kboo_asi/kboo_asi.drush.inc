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


function drush_kboo_asi_get_as_db() {
	$ftp_keys = file_get_contents(DRUPAL_ROOT . '/../ftp_login');
	list($ftp_host, $ftp_user, $ftp_pass) = explode("\n", $ftp_keys);
	$mysql_grab = file_get_contents(DRUPAL_ROOT . '/../ftp_mysql_getter');
	$mysql_grab = str_replace('$HOST', $ftp_host, $mysql_grab);
	$mysql_grab = str_replace('$USER', $ftp_user, $mysql_grab);
	$mysql_grab = str_replace('$PASSWORD', $ftp_pass, $mysql_grab);
	$datestr = date('Ymd', time() - 24*60*60); //yesterday's backup
	$mysql_grab = str_replace('YYYYMMDD', $datestr, $mysql_grab);
	$output = array();
	$result = 0;
	exec($mysql_grab, $output, $result);
	//downloads to /var/www/vhosts/test.kboo.fm/
print_r($result);
	return 'Downloaded';
}

function drush_kboo_asi_import_as_db() {
	$mysql_login = file_get_contents(DRUPAL_ROOT . '/../mysql_login');
	list($mysql_db, $mysql_user, $mysql_pass) = explode("\n", $mysql_login);

	$mysql_file = 'bitnami_resourcespaceYYYYMMDD2325.zip';
	$datestr = date('Ymd', time() - 24*60*60); //yesterday's backup
	$mysql_file = str_replace('YYYYMMDD', $datestr, $mysql_file);
	$mysql_file = DRUPAL_ROOT . '/../' . $mysql_file;

	$mysql_clean_file = __DIR__ . '/mysql_clean';
	$mysql_clean_command = 'sed \'s/<DBASE>/' . $mysql_db . '/\' ' . $mysql_clean_file . ' | mysql -u ' . $mysql_user . ' -p' . $mysql_pass . ' -D ' . $mysql_db;
	$cl_output = '';
	$cl_res = 0;
	exec($mysql_clean_command, $cl_output, $cl_res);

	$output = '';
	$mysql_command = 'unzip -p ' . $mysql_file . ' | sed \'s/bitnami_resourcespace/kboo_arcspace/\' | mysql -u ' . $mysql_user . ' -p' . $mysql_pass . ' -D ' . $mysql_db;
	$res = 0;
	exec($mysql_command, $output, $res);
print_r($cl_res);
print_r($res);
	return 'Success';
}

function drush_kboo_asi_check_as_db() {
#ftp_getter_template is the ftp template
}

