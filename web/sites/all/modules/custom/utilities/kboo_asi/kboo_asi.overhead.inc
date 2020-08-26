<?php
//file for importing etc functions

/*
function kboo_asi_check_updated_nodes()
{
	//checking our table for resources updated since our node update or creation
	$q = db_query("select * from kboo_asi_resource where asdate > drdate limit 30");
	while($r = $q->fetchObject())
	{
		$upnodes[] = $r->res;
	}

	if(count($upnodes) == 0)
	{
		return FALSE;
	}

	foreach($upnodes as $upnode)
	{
		if($node_info = kboo_asi_import_resource($upnode, TRUE))
		{
			db_query("update kboo_asi_resource set nid=:nid, drdate=:ddate where res=:res", array(':nid' => $node_info[0], ':ddate'=>$node_info[1], ':res' => $upnode));
		}
	}
	return TRUE;
}
*/

function kboo_asi_update_nodes_batch()
{
	$count = db_query("select count(*) as count from kboo_asi_resource where asdate > drdate")->fetchField();
	//we do 30 per run
	$runs = ceil($count/30);
	$ops = array();
	for($i=0; $i<$runs; $i++)
	{
		$ops[] = array('kboo_asi_check_updated_nodes', array());
	}
	$batch = array(
		'operations' => $ops,
		'finished' => 'kboo_asi_updated_nodes_batch_finish',
		'progress_message' => t('Processed @current of @total.'),
		'error_message' => t('Batch encountered an error.'),
	);
	batch_set($batch);
	batch_process('/admin/content');
	return 0;
}

function kboo_asi_updated_nodes_batch_finish($success, $results, $operations)
{
	if($success)
	{
		$msg = t('@count items processed', array('@count' => count($results)));
		$msg .= theme('item_list', array('items' => $results));
		drupal_set_message($msg);
	}
	else
	{
		$error_operation = reset($operations);
		$msg = t('Error occurred while processing %e_op with arguments @args', array('%e_op' => $error_operation[0], '@args' => print_r($error_operation[1], TRUE)));
		drupal_set_message($msg, 'error');
	}
}

function kboo_asi_no_nodes_batch()
{
	$count = db_query("select count(*) as count from kboo_asi_resource where nid is null")->fetchField();
#dpm($count, 'count');
	//we do 30 per run
	$runs = ceil($count/30);
	$ops = array();
	for($i=0; $i<$runs; $i++)
	{
		$ops[] = array('kboo_asi_check_no_nodes', array());
	}
	$batch = array(
		'operations' => $ops,
		'finished' => 'kboo_asi_no_nodes_batch_finish',
		'progress_message' => t('Processed @current of @total.'),
		'error_message' => t('Batch encountered an error.'),
	);
#dpm($ops);
	batch_set($batch);
	batch_process('/admin/content');
	return 0;
}

function kboo_asi_no_nodes_batch_finish($success, $results, $operations)
{
	if($success)
	{
		$msg = t('@count items processed', array('@count' => count($results)));
		$msg .= theme('item_list', array('items' => $results));
		drupal_set_message($msg);
	}
	else
	{
		$error_operation = reset($operations);
		$msg = t('Error occurred while processing %e_op with arguments @args', array('%e_op' => $error_operation[0], '@args' => print_r($error_operation[1], TRUE)));
		drupal_set_message($msg, 'error');
	}
}

function kboo_asi_proc_filequeue_batch_finish($success, $results, $operations)
{
	if($success)
	{
		$msg = t('@count items processed', array('@count' => count($results)));
		$msg .= theme('item_list', array('items' => $results));
		drupal_set_message($msg);
	}
	else
	{
		$error_operation = reset($operations);
		$msg = t('Error occurred while processing %e_op with arguments @args', array('%e_op' => $error_operation[0], '@args' => print_r($error_operation[1], TRUE)));
		drupal_set_message($msg, 'error');
	}
}

function kboo_asi_check_no_nodes(&$context)
{
	if(!isset($context['sandbox']['progress']))
	{
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['current_node'] = 0;
		$context['sandbox']['max'] = ceil(db_query("select count(*) as count from kboo_asi_resource where nid is null")->fetchField()/30);
	}


	//find resources that have no drupal node
	$nonodes = array();
	$q = db_query("select * from kboo_asi_resource where nid is null order by res asc limit 30");
	while($r = $q->fetchObject())
	{
		$nonodes[] = $r->res;
	}

	if(count($nonodes) == 0)
	{
		return FALSE;
	}

	foreach($nonodes as $nonode)
	{
		if($node_info = kboo_asi_import_resource($nonode))
		{
			db_query("update kboo_asi_resource set nid=:nid, drdate=:ddate where res=:res", array(':nid' => $node_info[0], ':ddate'=>$node_info[1], ':res' => $nonode));
		}
		$context['results'][] = $node_info[0];
		$context['sandbox']['progress']++;
		$context['sandbox']['current_node'] = $node_info[0];
		$context['message'] = "Completed node " . $nonode;
	}
	if($context['sandbox']['progress'] != $context['sandbox']['max'])
	{
		$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
	}
	return TRUE;
}

function kboo_asi_check_updated_nodes(&$context)
{
	if(!isset($context['sandbox']['progress']))
	{
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['current_node'] = 0;
		$context['sandbox']['max'] = ceil(db_query("select count(*) as count from kboo_asi_resource where asdate > drdate")->fetchField()/30);
	}


	//find resources that need update
	$upnodes = array();
	$q = db_query("select * from kboo_asi_resource where asdate > drdate order by res asc limit 30");
	while($r = $q->fetchObject())
	{
		$upnodes[] = $r->res;
	}

	if(count($upnodes) == 0)
	{
		return FALSE;
	}

	foreach($upnodes as $upnode)
	{
		if($node_info = kboo_asi_import_resource($upnode, TRUE))
		{
			db_query("update kboo_asi_resource set drdate=:ddate where res=:res", array(':ddate'=>$node_info[1], ':res' => $upnode));
		}
		$context['results'][] = $node_info[0];
		$context['sandbox']['progress']++;
		$context['sandbox']['current_node'] = $node_info[0];
		$context['message'] = "Completed node " . $upnode;
	}
	if($context['sandbox']['progress'] != $context['sandbox']['max'])
	{
		$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
	}
	return TRUE;
}

function kboo_asi_populate_res_log()
{
	//this moves records from resource_log in archivespace db to the drupal db.  it only records resource id and date of last edit.  we store
	//ref (= id of most recent edit) in a drupal var
	//actual imports will come later from a comparison between the two date fields in the kboo_asi_resource table

	//way to run this optimally will involve batch the first time around, or just hit it many times until max ref = tablesize of resource_log
	//followup runs should be much smaller

	//we store "max ref" in a drupal var.  this refers to the last edit recorded in resource_log table of archivespace db.  ref is a serial.
	$ref_count = variable_get("kboo_asi_edit_max_ref", 0);
	$current_refs = array();
	db_set_active('archive');
	$q = db_query('select rl.ref, rl.resource, rl.date from resource_log as rl inner join resource as r on rl.resource=r.ref where rl.ref > :d order by rl.ref asc limit 5000', array(':d' => $ref_count));
	while($r = $q->fetchObject())
	{
		$current_refs[] = array($r->resource, $r->date, $r->ref);
	}
	db_set_active('default');

	if(count($current_refs) == 0)
	{
		return FALSE;
	}

	//insert-update the drupal table and var
	foreach($current_refs as $ref)
	{
		db_query('insert into kboo_asi_resource (res, asdate) values (:r, :ad) on duplicate key update asdate=:ad', array(':r' => $ref[0], ':ad' => $ref[1]));
		variable_set("kboo_asi_edit_max_ref", $ref[2]);
	}
	return TRUE;
}

function kboo_asi_latest_db($pp = FALSE)
{
	//date of latest db
	$path = '/var/www/vhosts/test.kboo.fm/rs_dls';
	$files = scandir($path);
	$hits = array();
	foreach($files as $file)
	{
		if(substr($file, 0, 21) == 'bitnami_resourcespace')
		{
			$hits[] = $file;
		}
	}
	$latest = 0;
	foreach($hits as $hit)
	{
		$datestr = substr($hit, 21, 8);
		if($datestr > $latest)
		{
			$latest = $datestr;
		}
	}
	if($pp)
	{
		$y = substr($latest, 0, 4);
		$m = substr($latest, 4, 2);
		$d = substr($latest, 6, 2);
		return $m . '/' . $d . '/' . $y;
	}
	return $latest;
}

function kboo_asi_db_uptodate($del=FALSE, $verbose = TRUE)
{
	//parameters:
	//	$del if true, will delete old db zips
	//	$verbose for text output; else will return TRUE/FALSE for db check; T/F return
	//		has no relation to deletion of old files

	//downloader downloads to /var/www/vhosts/test.kboo.fm/rs_dls
	//filename convention is: bitnami_resourcespace201911242325.zip
	//ie: bitnami_resourcespaceYYYYMMDD2325.zip ...  2325 must be the time the archive runs

	//this is where we download the archive zip from the archive server
	$path = '/var/www/vhosts/test.kboo.fm/rs_dls';
	$files = scandir($path);
	$hits = array();
	foreach($files as $file)
	{
		if(substr($file, 0, 21) == 'bitnami_resourcespace')
		{
			$hits[] = $file;
		}
	}
	$today = date('Ymd', time() - 24*60*60);

	//separate old from current
	$dels = array();
	$live = array();
	foreach($hits as $hit)
	{
		$datestr = substr($hit, 21, 8);
		if($datestr != $today)
		{
			$dels[] = $hit;
		}
		else
		{
			$live[] = $hit;
		}
	}

	$out = '';
	if($del)
	{
		foreach($dels as $del)
		{
			$res = unlink($path . '/' . $del);
			if($res)
			{
				$out .= "<br>Deleted: " . $del;
			}
		}
	}

	if(!empty($live))
	{
		//then we have one dated yesterday, so we are up to date
		if(!$verbose)
		{
			return TRUE;
		}
		else
		{
			$out .= "<br>We have an up to date db.";
		}
	}
	else
	{
		//we're not, so return false
		$out .= "<br>Current db out of date.";
		if(!$verbose)
		{
			return FALSE;
		}
	}
	return $out;
}

function kboo_asi_get_as_file($path, $file)
{
	//this downloads the argument file from the archive server
	$ftp_keys = file_get_contents(DRUPAL_ROOT . '/../ftp_login');
	list($ftp_host, $ftp_user, $ftp_pass) = explode("\n", $ftp_keys);
	$filegrab = file_get_contents(DRUPAL_ROOT . '/../ftp_getter_template');
	$filegrab = str_replace('$HOST', $ftp_host, $filegrab);
	$filegrab = str_replace('$USER', $ftp_user, $filegrab);
	$filegrab = str_replace('$PASSWORD', $ftp_pass, $filegrab);
	$filegrab = str_replace('<DIR>', $path, $filegrab);
	$filegrab = str_replace('<FILE>', $file, $filegrab);
	$output = array();
	$result = 0;
	exec($filegrab, $output, $result);
	if(substr($output[11], 0, 3) == '550')
	{
		//retry with filename as dir
		$filegrab = file_get_contents(DRUPAL_ROOT . '/../ftp_getter_template');
		$filegrab = str_replace('$HOST', $ftp_host, $filegrab);
		$filegrab = str_replace('$USER', $ftp_user, $filegrab);
		$filegrab = str_replace('$PASSWORD', $ftp_pass, $filegrab);

		$nfile = explode('.', $file);
		$npath = $path . '/' . $nfile[0];
		$filegrab = str_replace('<DIR>', $npath, $filegrab);
		$filegrab = str_replace('<FILE>', $file, $filegrab);
		$output = array();
		$result = 0;
		exec($filegrab, $output, $result);

		if(substr($output[11], 0, 3) == '550')
		{
			//also write a file to record missing ones
			$f = fopen(DRUPAL_ROOT . '/../rs_dls/missing_files', 'a');
			fwrite($f, "Missing file: " . $path . "/" . $file . " and " . $npath . "/" . $file . "\n");
			fclose($f);
			return 550;
		}
	}
	//downloads to /var/www/vhosts/test.kboo.fm/rs_dls
	if(file_exists(DRUPAL_ROOT . '/../rs_dls/' . $file))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

function kboo_asi_get_as_db($drush = FALSE)
{
	//this downloads the database from the archive server
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
	$ex = exec($mysql_grab, $output, $result);
	//downloads to /var/www/vhosts/test.kboo.fm/rs_dls
	if($drush)
	{
print_r($result, TRUE);
		return 'Downloaded';
	}
	else
	{
		return TRUE;
	}
}

function kboo_asi_import_as_db($drush = FALSE, $retdate = FALSE)
{
	//this imports the db dated yesterday (assuming it exists!) to the archivespace working db
	$mysql_login = file_get_contents(DRUPAL_ROOT . '/../mysql_login');
	list($mysql_db, $mysql_user, $mysql_pass) = explode("\n", $mysql_login);

	$mysql_file = 'bitnami_resourcespaceYYYYMMDD2325.zip';
	if($retdate)
	{
		$path = DRUPAL_ROOT . '/../rs_dls/';
		$files = scandir($path);
		$hits = array();
		$maxdate = '';
		foreach($files as $file)
		{
			if(substr($file, 0, 21) == 'bitnami_resourcespace')
			{
				$d = substr($file, 21, 8);
				if($d > $maxdate)
				{
					$maxdate = $d;
				}
			}
		}

		$datestr = $maxdate;
		$mysql_file = str_replace('YYYYMMDD', $datestr, $mysql_file);
		$mysql_fileret = $mysql_file;
	}
	else
	{
		$datestr = date('Ymd', time() - 24*60*60); //yesterday's backup
		$mysql_file = str_replace('YYYYMMDD', $datestr, $mysql_file);
		$mysql_fileret = $mysql_file;
	}
	$mysql_file = DRUPAL_ROOT . '/../rs_dls/' . $mysql_file;

	$mysql_clean_file = __DIR__ . '/mysql_clean';
	$mysql_clean_command = 'sed \'s/<DBASE>/' . $mysql_db . '/\' ' . $mysql_clean_file . ' | mysql -u ' . $mysql_user . ' -p' . $mysql_pass . ' -D ' . $mysql_db;
	$cl_output = '';
	$cl_res = 0;
	exec($mysql_clean_command, $cl_output, $cl_res);

	$output = '';
	$mysql_command = 'unzip -p ' . $mysql_file . ' | sed \'s/bitnami_resourcespace/kboo_arcspace/\' | mysql -u ' . $mysql_user . ' -p' . $mysql_pass . ' -D ' . $mysql_db;
	$res = 0;
	exec($mysql_command, $output, $res);
	if($drush)
	{
print_r($cl_res, TRUE);
print_r($res, TRUE);
		return 'Success';
	}
	else if($retdate)
	{
		return $mysql_fileret;
	}
	else
	{
		return TRUE;
	}
}

function _kboo_asi_gen_list($list, $header, $caption, $el)
{
	return theme_table(array('header' => $header, 'rows' => $list, 'footer' => array(), 'attributes' => array('class' => 'kboo-asi-admin-table'), 'caption' => $caption, 'colgroups' => array())) . theme('pager', array('tags' => array(), 'element' => $el));
}
