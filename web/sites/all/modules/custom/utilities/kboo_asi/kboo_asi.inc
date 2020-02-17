<?php

function kboo_asi_import_resource($res, $update = FALSE)
{
	//here's the meat.  must return an array containing node id and date of update.  check format of that date.
	//argument is a resource id from archive space.  not a node id
	//this operates on one resource

	$data = array();
	//grab all the data we need from resource space db for this resource.
	$res_rdata = kboo_asi_get_rdata($res);
	if($res_rdata === FALSE)
	{
		$q = db_query("delete from kboo_asi_resource where res=:r", array(':r'=>$res));
		return FALSE;
	}
 	//$res_rdata has 'Date' key pointing to string 'YYYY-MM-DD' maps to air date
	//	'Contributor' key to string 'Firstname Lastname' maps to hosted by
	//	'Program Name' key to string program name; if empty choose 'Treasures from the KBOO Archives', maps to Program
	//	'Publisher' key to produced by, default to 'KBOO'
	//	'Written notes on casing' to body/episode description
	//	'Item Title' to title, presumably

	if($update)
	{
		$nid = db_query("select nid from kboo_asi_resource where res=:r", array(':r' => $res))->fetchObject()->nid;
		$n = node_load($nid);
	}
	else
	{
		$n = new stdClass();
		$n->type = 'station_content';
		node_object_prepare($n);
		$n->uid = 1;
		$n->language = 'en';
		$n->status = 1;
		$n->promote = 0;
		$n->revision = 0;
	}
	if(strlen($res_rdata['Item Title']) > 255)
	{
		$n->title = substr($res_rdata['Item Title'], 0, 255);
		$title = $res_rdata['Item Title'] . "\n\n";
	}
	else
	{
		$n->title = $res_rdata['Item Title'];
		$title = '';
	}

	//these two are entity references, so we look up the nid of the target label
	if(isset($res_rdata['Contributor']))
	{
		$n->field_hosted_by['und'][0]['target_id'] = kboo_asi_host_lookup($res_rdata['Contributor']);
	}

	if(empty($res_rdata['Program Name']))
	{
		$progname = 'Treasures from the KBOO Archives';
	}
	else
	{
		$progname = $res_rdata['Program Name'];
	}
	$n->field_produced_for['und'][0]['target_id'] = kboo_asi_program_lookup($progname);

	if(empty($res_rdata['Publisher']))
	{
		$publisher = 'KBOO';
	}
	else
	{
		$publisher = $res_rdata['Publisher'];
	}
	$n->field_produced_by['und'][0]['value'] = $publisher;
	$n->field_produced_by['en'][0]['value'] = $publisher;

	if(!empty($res_rdata['Written notes on casing'])) #ternary works too
	{
		$body = $res_rdata['Written notes on casing'];
	}
	else
	{
		$body = '';
	}
	$n->body['und'][0]['value'] = $title . $body;
	$n->body['en'][0]['value'] = $title . $body;

	if(isset($res_rdata['Date']))
	{
		$airdate = kboo_asi_grab_airdate($res_rdata['Date'], $res);
	}

	if(!empty($airdate))
	{
		if($airdate->format('U') >= 0)
		{
			$using_timestamp = TRUE;
			$n->field_air_time['und'][0]['value'] = $airdate->format('U');
		}
		else
		{
			$using_timestamp = FALSE;
			$n->field_air_time_old['und'][0]['value'] = $airdate->format('Y-m-d G:i');
		}

		if(isset($res_rdata['Duration Physical']))
		{
			$duration = $res_rdata['Duration Physical'];
			$durparts = explode(':', $duration);
			//this handles at least one with "-05" as a duration element.
			foreach($durparts as $dk=>$dp)
			{
				if(!is_int($dp))
				{
					$durparts[$dk] = abs((int)$dp);
				}
			}
			if(count($durparts) == 2)
			{
				$airdate->add(new DateInterval('PT' . $durparts[0] . 'M' . $durparts[1] . 'S'));
			}
			else
			{
				$airdate->add(new DateInterval('PT' . $durparts[0] . 'H' . $durparts[1] . 'M' . $durparts[2] . 'S'));
			}
		}
		else
		{
			$durparts = array(1, 0, 0);
		}

		if($using_timestamp)
		{
			$n->field_air_time['und'][0]['value2'] = $airdate->format('U');
		}
		else
		{
			$n->field_air_time_old['und'][0]['value2'] = $airdate->format('Y-m-d G:i');
		}
		$n->field_air_time['und'][0]['timezone'] = 'America/Los_Angeles';
		$n->field_air_time['und'][0]['timezone_db'] = 'UTC';
		$n->field_air_time['und'][0]['timezone_db'] = 'datestamp';
	}

	node_submit($n);
	node_save($n);


	$files = kboo_asi_get_files($res, $res_rdata);
	//this will only queue the files, not actually attach them.

	//first flush queue for this node & resource
	//these will have to be queued because any file could take a while to download and this
	//could break normal batch
	//downloading function is kboo_asi_get_as_file($path, $file)
	$q = db_delete('kboo_asi_res_files')->condition('nid', $n->nid)->condition('res', $res)->execute();
	foreach($files as $file)
	{
		$q = db_insert('kboo_asi_res_files')->fields(array('res'=>$res, 'nid'=>$n->nid, 'filename'=>$file['name'], 'filepath'=>$file['path']))->execute();
	}

	return array($n->nid, date('Y-m-d G:i:s'));
}

function kboo_asi_grab_airdate($date, $res)
{
	if(empty(trim($date)))
	{
		return kboo_asi_grab_date_from_kw($res);
	}

	if(strpos($date, '/') !== FALSE)
	{
		//then we have slashes, try from kw  (this is specifically because of those resources
		//looking like this.  not necessarily because the algorithm is better
		$airdate = kboo_asi_grab_date_from_kw($res);
	}
	else
	{
		if(is_numeric($date)) //then we have a number w/ no delimiter eg YYYYMMDD
		{
			if(strlen($date) == 8)
			{
				//then we're dealing with YYYYMMDD
				$dparts = array(substr($date, 0, 4), substr($date, 4, 2), substr($date, 6, 2));
			}
			else if(strlen($date) == 6)
			{
				//then we're dealing with YYYYMM
				$dparts = array(substr($date, 0, 4), substr($date, 4, 2), '01');
			}
			else
			{
				//then we're dealing with YYYY or YY
				if(strlen($date) == 4)
				{
					$dparts = array($date, '01', '01');
				}
				else
				{
					$yr = $date > 20 ? '19' . $date : '20' . $date;
					$dparts = array($yr, '01', '01');
				}
			}
		}
		else //we expect delimiter '-'
		{
			$dparts = explode('-', $date);
		}

		//now we have dparts
		if(count($dparts) == 3)
		{
			$airdate = DateTime::createFromFormat('Y-m-d G:i', $dparts[0] . '-' . $dparts[1] . '-' .  $dparts[2] . ' 12:00');
		}
		else if(count($dparts) == 2)
		{
			$airdate = DateTime::createFromFormat('Y-m-d G:i', $dparts[0] . '-' . $dparts[1] . '-01' . ' 12:00');
		}
		else //dparts is only one... ie string situation.  shouldn't get here logically because of is_numeric check above 
		{
			if(strlen($date) == 4) // then assume a year
			{
				$airdate = DateTime::createFromFormat('Y-m-d G:i', $date . '-01-01' . ' 12:00');
			}
			else
			{
				//try to grab it from the keywords
				$airdate = kboo_asi_grab_date_from_kw($res);
			}
		}
	}
	return $airdate;
}

function kboo_asi_grab_date_from_kw($res)
{
	$kw = kboo_asi_get_keywords($res);
	if(isset($kw['Date']))
	{
		$dstr = '';
		switch(count($kw['Date']))
		{
			case 1:
				$dstr .= $kw['Date'][0] . '-01-01';
				break;
			case 2:
				$dstr .= $kw['Date'][0] . '-' . $kw['Date'][1] . '-01';
				break;
			case 3:
				if(strlen($kw['Date'][0]) == 4) //then 0 is year, format is YYYY-x-x
				{
					$dstr .= $kw['Date'][0] . '-' . $kw['Date'][1] . '-' . $kw['Date'][2];
				}
				else if(strlen($kw['Date'][2]) == 4) //then 2 is year, format is x-x-YYYY
				{
					$dstr .= $kw['Date'][2] . '-' . $kw['Date'][1] . '-' . $kw['Date'][0];
				}
				else
				{
					//no idea, check size
					$ar = array($kw['Date'][0], $kw['Date'][1], $kw['Date'][2]);
					sort($ar);
					$yr = array_pop($ar);
					$day = array_pop($ar);
					$mo = array_pop($ar);
					$dstr .= $yr .'-' . $mo . '-' . $day;
				}
				break;
		}
		if(!empty($dstr))
		{
			$airdate = DateTime::createFromFormat('Y-m-d G:i', $dstr . ' 12:00');
		}
	}
	return $airdate;
}

function kboo_asi_proc_filequeue()
{
	//this will have to delete files on existing node (ie in the event that an update
	//decreases number of files or changes an existing file) in such a way that drupal de-attaches
	//them from the node and deletes the files (else updates could very quickly clog the server with
	//duplicate files).  then it imports the new files.  import = download from archivespace, create in
	//drupal filesystem, attach to pertinent node


	//find a group associated with one res
	//in practice there are few with multiple files
	$q = db_query("select max(filename),max(res) as res, min(status) as status from kboo_asi_res_files where status < 4 or status is null group by res");
	#$q = db_query("select * from kboo_asi_res_files where res=:r", array(':r' => 11850));
	while($r = $q->fetchObject())
	{
		//in other words we have a problem... skip it.
		if($r->status > 3)
		{
			continue;
		}
		//process for that group
		kboo_asi_proc_filegroup($r->res);
	}
	
	return 'Completed';
}

function kboo_asi_proc_filegroup($res)
{
	//grab nid from resource table
	$q=db_query("select * from kboo_asi_resource where res=:r", array(':r' => $res));
	if($r=$q->fetchObject())
	{
		$nid=$r->nid;
	}
	else
	{
		return FALSE;
	}

	//out with the old
	$n = node_load($nid);
	$dels = array();
	if(isset($n->field_audio_files['und']))
	{
		foreach($n->field_audio_files['und'] as $key=>$file)
		{
			$f = file_load($file['fid']);
			$dels[] = $f;
			$n->field_audio_files['und'][$key] = array();
		}
		node_save($n);
		foreach($dels as $del)
		{
			file_delete($del);
		}
	}

	//in with the new
	$ops = array();
	$q = db_query("select * from kboo_asi_res_files where res=:r", array(':r' => $res));
	while($r=$q->fetchObject())
	{
		$ops[] = array('kboo_asi_fetch_file', array($r->res, $r->filename, $r->filepath, $nid, $q->rowCount()));
		//update status on this file in batch '1' = 'batch set'
		if(kboo_asi_checkstat($res, $r->filename) < 1)
		{
			kboo_asi_checkstat($res, $r->filename, 1);
		}
	}

	$batch = array(
		'operations' => $ops,
		'finished' => 'kboo_asi_proc_filequeue_batch_finish',
		'progress_message' => t('Processed @current of @total.'),
		'error_message' => t('Batch encountered an error.'),
	);
	batch_set($batch);
	//return to filequeue until all processed
	batch_process('/kboo/asi/proc_filequeue');
	return TRUE;
}

function kboo_asi_checkstat($res, $name, $update=NULL)
{
	if(isset($update))
	{
		$q=db_query('update kboo_asi_res_files set status=:stat where res=:r and filename=:fn', array(':stat'=>$update, ':r'=>$res, ':fn'=>$name));
	}
	$status = db_query("select status from kboo_asi_res_files where res=:r and filename=:fn", array(':r'=>$res, ':fn'=>$name))->fetchObject()->status;
	return $status;
}

function kboo_asi_fetch_file($res, $name, $path, $nid, $count, &$context)
{
	if(!isset($context['sandbox']['progress']))
	{
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['current_node'] = 0;
		$context['sandbox']['max'] = $count;
	}

	//check file status
	$status = kboo_asi_checkstat($res, $name);
	if($status < 3)
	{
		//update file status to '2' == 'fetching'
		kboo_asi_checkstat($res, $name, 2);
	}

	//downloads to /var/www/vhosts/test.kboo.fm/rs_dls
	//unless status = 3 (already downloaded)
	if($status == 3 || $gf = kboo_asi_get_as_file($path, $name))
	{
		if(isset($gf) && $gf === 550)
		{
			//status 10 is 'file not found'
			kboo_asi_checkstat($res, $name, 10);
			return FALSE;
		}

		//otherwise file exists by return status, see kboo_asi_get_as_file
		//so update db, status 3='have the file locally in work dir'
		kboo_asi_checkstat($res, $name, 3);

		//drupalize it
		$source = DRUPAL_ROOT . '/../rs_dls/' . $name;
		$target = 'public://audio/station_content/' . $name;
		$file = file_save_data(file_get_contents($source), $target, FILE_EXISTS_RENAME);
		if($file)
		{
			$file->status = FILE_STATUS_PERMANENT;
			$file = file_save($file);
			//15 is "exists, managed, and located at correct URI"
			kboo_asi_checkstat($res, $name, 15);
			$n = node_load($nid);
			$file->display = 1;
			if(substr($file->filemime, 0, 5) == 'audio')
			{
				$n->field_audio_files['und'][] = (array) $file;
			}
			else if(substr($file->filemime) == 'image')
			{
				$n->field_more_images['und'][] = (array) $file;
			}
			node_save($n);
			//20 is "exists, managed, and attached to it's node"
			kboo_asi_checkstat($res, $name, 20);

			//delete work copy
			if(file_exists(DRUPAL_ROOT . '/../rs_dls/' . $name))
			{
				unlink(DRUPAL_ROOT . '/../rs_dls/' . $name);
			}
		}

		$context['results'][] = $name;
		$context['sandbox']['progress']++;
		$context['sandbox']['current_resource'] = $res;
		$context['message'] = "Completed file " . $name;
	}
	else
	{
		return FALSE;
	}


	if($context['sandbox']['progress'] != $context['sandbox']['max'])
	{
		$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
	}
	return TRUE;
}

/*
//file will go in field_audio_files
$file_temp = file_get_contents('public://someimage.jpg');

// Saves a file to the specified destination and creates a database entry.
$file_temp = file_save_data($file_temp, 'public://' . 'someimage.jpg', FILE_EXISTS_RENAME);

$node->field_page_image = array(
  'und' => array(
    0 => array(
      'fid' => $file_temp->fid,
      'filename' => $file_temp->filename,
      'filemime' => $file_temp->filemime,
      'uid' => 1,
      'uri' => $file_temp->uri,
      'status' => 1,
      'display' => 1
    )
  )
);


*/

/*
//kboo_asi_get_keywords($res);
$out = 'keywords: <br>' . print_r($j, TRUE);
dpm($j, 'keywords on it');
$j = kboo_asi_get_rdata(15715);
$out .= 'resource data:<br>' . print_r($j, TRUE);
dpm($j, 'resource data on it');
$j = kboo_asi_get_files(15715);
$out .= 'files: <br>' . print_r($j, TRUE);
*/



function kboo_asi_program_lookup($progname)
{
#dpm($progname, 'progname');
	$progname_trunc = substr($progname, 0, 255);
	$q = db_query("select * from node where type='program' and title like :s", array(':s' => $progname_trunc));
	if($r = $q->fetchObject())
	{
		return $r->nid;
	}
	else
	{
		//create it.
		$n = new stdClass();
		$n->type = 'program';
		node_object_prepare($n);
		$n->uid = 1;
		$n->title = $progname_trunc;
		$n->language = 'en';
		$n->status = 1;
		$n->promote = 0;
		$n->revision = 0;
		$n->field_published_date['und'][0] = array(
			'value' => date('Y-m-d'),
			'timezone' => 'America/Los_Angeles',
			'timezone_db' => 'UTC',
			'date_type' => 'datetime',
		);
		$n->field_produced_by['und'][0] = array(
			'value' => 'KBOO',
			'format' => null,
			'safe_value' => 'KBOO',
		);
		if(strlen($progname) > 255)
		{
			$n->body['und'][0]['value'] = $progname;
			$n->body['en'][0]['value'] = $progname;
		}
		$n->field_program_status['und'][0]['value'] = 0; //current
		$n->field_substitute['und'][0]['value'] = 0;
		$n->title_field['en'][0] = array(
			'value' => $progname_trunc,
			'format' => null,
			'safe_value' => $progname_trunc,
		);
		#?$n->title_original = $progname;
		node_submit($n);
		node_save($n);
		return $n->nid;
	}

}

function kboo_asi_host_lookup($hostname)
{
	$hostname_trunc = substr($hostname, 0, 255);
	$q = db_query("select * from node where type='person_profile' and title like :s", array(':s' => $hostname_trunc));
	if($r = $q->fetchObject())
	{
		return $r->nid;
	}
	else
	{
		//create it.
		$n = new stdClass();
		$n->type = 'person_profile';
		node_object_prepare($n);
		$n->uid = 1;
		$n->title = $hostname_trunc;
		$n->language = 'en';
		$n->status = 1;
		$n->promote = 0;
		$n->revision = 0;
		$n->field_profile_type['und'][0]['tid'] = 10; //refers to host
		$n->field_published_date['und'][0] = array(
			'value' => date('Y-m-d'),
			'timezone' => 'America/Los_Angeles',
			'timezone_db' => 'UTC',
			'date_type' => 'datetime',
		);
		if(strlen($hostname) > 255)
		{
			$n->body['und'][0]['value'] = $hostname;
			$n->body['en'][0]['value'] = $hostname;
		}
		$n->field_show_host_status['und'][0]['value'] = 1;
		$n->field_substitute['und'][0]['value'] = 0;
		$n->title_field['en'][0] = array(
			'value' => $hostname_trunc,
			'format' => null,
			'safe_value' => $hostname_trunc,
		);
		#?$n->title_original = $hostname_trunc;
		node_submit($n);
		node_save($n);
		return $n->nid;
	}
}

function kboo_asi_get_rdata($ref)
{
	//grabs resource data for one resource id'd by $ref
	$keys = kboo_asi_get_keys();
	db_set_active('archive');
	$data = array();
	$q = db_query('select * from resource_data where resource=:r', array(':r' => $ref));
	while($r = $q->fetchObject())
	{
		$val = $r->value;
		if(substr($val, 0, 1) == ',')
		{
			$val = substr($val, 1);
		}
		$val = trim($val);
		if(!isset($keys[$r->resource_type_field]))
		{
			$data['unknown label'][] = $val;
		}
		else
		{
			$data[$keys[$r->resource_type_field]['title']] = $val;
		}
	}
	db_set_active('default');
#dpm($data, 'in get rdata');
	if(empty($data))
	{
		return FALSE;
	}
	return $data;
}

function kboo_asi_get_files($ref, $data)
{
	//grabs files referenced by resource
	db_set_active('archive');
	$files = array();
/*
	$q = db_query('select * from resource as r inner join resource_data as rd on rd.resource=r.ref and r.file_extension=:ext and r.ref=:r and rd.resource_type_field in (101, 102)', array(':r' => $ref, ':ext' => 'mp3'));
	while($r = $q->fetchObject())
	{
	}
*/
	if(isset($data['Proxy Filename']))// && isset($data['Preservation File Location']))
	{
		/*
		$path = explode('/', $data['Preservation File Location']);
		array_pop($path);
		array_shift($path);
		$path = '/' . implode('/', $path);
		*/
		//^^^ those paths are unreliable.  we derive from filename
		$path = kboo_asi_get_filepath($data['Proxy Filename']);
		$files[] = array('name' => $data['Proxy Filename'], 'path' => $path);
	}
	$q = db_query('select * from resource_alt_files where resource=:r and file_extension=:ext', array(':r' => $ref, ':ext' => 'mp3'));
	while($r = $q->fetchObject())
	{
		$path = kboo_asi_get_filepath($r->file_name);
#dpm($r, 'file info inside file info grab');
		if($path === FALSE)
		{
			continue;
		}
		$files[] = array('name' => $r->file_name, 'path' => $path, 'size' => $r->file_size);
	}
	db_set_active('default');
	return $files;
	#
	# of interest:
	# 	if filename is of type kboo_CS then file in cassette
	# 	if filename is of type kboo_CD then file in cd directory
	# 	if filename is of type kboo_D then file in dat directory
	# 	if filename is of type kboo_M then file in minidisc directory
	# 	if filename is of type kboo_<number> then file in openreel directory
	#	
	#	all are subdirs of __final
}

function kboo_asi_get_filepath($fname)
{
	$pref = substr($fname, 0, 7);
	#build path
	if(substr($pref, 0, 5) == 'kboo_')
	{
		#then strip prefix
		$pref = substr($pref, 5, 2);
	}
	$path = '/_final/';
	if(substr($pref, 0, 2) == 'CS')
	{
		$path .= 'cassette';
	}
	else if(substr($pref, 0, 2) == 'CD')
	{
		$path .= 'cd';
	}
	else if(substr($pref, 0, 1) == 'D')
	{
		$path .= 'dat';
	}
	else if(substr($pref, 0, 1) == 'M')
	{
		$path .= 'minidisc';
	}
	else if(is_numeric(substr($pref, 0, 1)))
	{
		$path .= 'openreel';
	}
#dpm($r, 'file info inside file info grab');
	return $path;
}

function kboo_asi_get_keywords($ref)
{
	//grabs keywords associated with a resource
	$keys = kboo_asi_get_keys();
	db_set_active('archive');
	$keywords = array();
	$q = db_query('select * from resource_keyword as rk left join keyword as k on rk.keyword=k.ref where rk.resource=:r', array(':r' => $ref));
	while($r = $q->fetchObject())
	{
		if(!isset($keys[$r->resource_type_field]))
		{
			$keywords['unknown label'][] = $r->keyword;
		}
		else
		{
			$keywords[$keys[$r->resource_type_field]['title']][$r->position] = $r->keyword;
		}
	}
	db_set_active('default');
	return $keywords;
}

function kboo_asi_get_keys()
{
	//grab field keys
	$keys = variable_get('kboo_as_field_keys', array());
	if(TRUE)//if(!isset($keys['stamp']) || $keys['stamp'] + 24*60*60 < time())
	{
		$fkeys = array();
		//then it's more than a day old so we fetch new values
		db_set_active('archive');
		$q = db_query('select ref, name, title from resource_type_field order by ref asc');
		while($r = $q->fetchObject())
		{
			$fkeys[$r->ref] = array('name' => $r->name, 'title' => $r->title);
		}
		$keys = array('stamp' => time(), 'keys' => $fkeys);
		db_set_active('default');
		variable_set('kboo_as_field_keys', $keys);
	}
	return $keys['keys'];
}
