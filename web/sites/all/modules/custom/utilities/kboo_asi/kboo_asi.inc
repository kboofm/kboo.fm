<?php

function kboo_asi_import_resource($res)
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

#dpm($res_rdata, 'rdata');
	$n = new stdClass();
	$n->type = 'station_content';
	node_object_prepare($n);
	$n->uid = 1;
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
	$n->language = 'en';
	$n->status = 1;
	$n->promote = 0;
	$n->revision = 0;

	//these two are entity references, so we look up the nid of the target label
	$n->field_hosted_by['und'][0]['target_id'] = kboo_asi_host_lookup($res_rdata['Contributor']);

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

	node_submit($n);
	node_save($n);


	$files = kboo_asi_get_files($res);
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

	return array($n->nid, date('Y-m-d H:i:s'));
}

function kboo_asi_proc_filequeue()
{
	//this will have to delete files on existing node (ie in the event that an update
	//decreases number of files or changes an existing file) in such a way that drupal de-attaches
	//them from the node and deletes the files (else updates could very quickly clog the server with
	//duplicate files).  then it imports the new files.  import = download from archivespace, create in
	//drupal filesystem, attach to pertinent node


	//find a group associated with one res
	$q = db_query("select max(filename),res,nid from kboo_asi_res_files group by res");
	while($r = $q->fetchObject())
	{
		//process for that group
		kboo_asi_proc_filegroup($r->res, $r->nid);
	}
	
	return;
}

function kboo_asi_proc_filegroup($res, $nid=NULL)
{
	if(empty($nid))
	{
		//then grab nid from resource table
		$q=db_query("select * from kboo_asi_resource where res=:r", array(':r' => $res));
		if($r=$q->fetchObject())
		{
			$nid=$r->nid;
		}
		else
		{
			return FALSE;
		}
	}

	//out with the old
	$n = node_load($nid);
	$dels = array();
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

	//in with the new
	$ops = array();
	$q = db_query("select * from kboo_asi_res_files where res=:r", array(':r' => $res));
	while($r=$q->fetchObject())
	{
		$ops[] = array('kboo_asi_fetch_file', array($r->res, $r->filename, $r->filepath, $nid, $r->rowCount()));
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
	return;
}

function kboo_asi_fetch_file(&$context, $res, $name, $path, $nid, $count)
{
	if(!isset($context['sandbox']['progress']))
	{
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['current_node'] = 0;
		$context['sandbox']['max'] = $count;
	}


	//kboo_asi_get_as_file($path, $file)
	//downloads to /var/www/vhosts/test.kboo.fm/rs_dls
	if(kboo_asi_get_as_file($path, $name))
	{
		//drupalize it
		$source = DRUPAL_ROOT . '/../rs_dls/' . $name;
		$target = 'public://audio/station_content/';
		$file = file_save_upload($source, array(), $target, FILE_EXISTS_RENAME);
		if($file)
		{
			$file->status = FILE_STATUS_PERMANENT;
			file_save($file);
			$n = node_load($nid);
			$n->field_audio_files['und'][] = (array) $file;
			node_save($n);
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


	if($context['sandbox']['progress'] != $context['sandbox']['max'])
	{
		$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
	}
	return TRUE;
}

/*
$file = file_save_upload('document', array(
    'file_validate_extensions' => array('txt doc'), // Validate extensions.
));
if ($file) {
// Move the file, into the Drupal file system
if ($file = file_move($file, 'public://')) {
  $file->status = FILE_STATUS_PERMANENT;
 // $file->file_display = 1;
  $file = file_save($file);
  //set the extra values needed to make node_save work
  $file->display = 1;
  $file->description = "";
} else {
  $output = t('Failed to write the uploaded file the site\'s file folder.');
}       
 } else {
$output = t('No file was uploaded.');
 }
$node->field...[und][0] = (array)$file;

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

#dpm($n);
#dpm($n, 'saved node');
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
#dpm($n, 'submitted program node');
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
#dpm($hostname, 'hostname');
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
#dpm($n, 'submitted person node');
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
#dpm($ref, 'ref in get rdata');
#dpm($data, 'in get rdata');
	if(empty($data))
	{
		return FALSE;
	}
	return $data;
}

function kboo_asi_get_files($ref)
{
	//grabs files referenced by resource
	db_set_active('archive');
	$files = array();
	$q = db_query('select * from resource_alt_files where resource=:r and file_extension=:ext', array(':r' => $ref, ':ext' => 'mp3'));
	while($r = $q->fetchObject())
	{
		$pref = substr($r->file_name, 0, 7);
		#build path
		if(substr($pref, 0, 5) != 'kboo_')
		{
			#then not a known path; skip the file
			continue;
		}
		else
		{
			$path = '/_final/';
			if(substr($pref, 5, 2) == 'CS')
			{
				$path .= 'cassette';
			}
			else if(substr($pref, 5, 2) == 'CD')
			{
				$path .= 'cd';
			}
			else if(substr($pref, 5, 1) == 'D')
			{
				$path .= 'dat';
			}
			else if(substr($pref, 5, 1) == 'M')
			{
				$path .= 'minidisc';
			}
			else if(is_numeric(substr($pref, 5, 1)))
			{
				$path .= 'openreel';
			}
		}
dpm($r, 'file info inside file info grab');
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
		//then it's more than a day old so we fetch new values
		db_set_active('archive');
		$q = db_query('select ref, name, title from resource_type_field order by ref asc');
		while($r = $q->fetchObject())
		{
			$keys[$r->ref] = array('name' => $r->name, 'title' => $r->title);
		}
		$keys = array('stamp' => time(), 'keys' => $keys);
		db_set_active('default');
		variable_set('kboo_as_field_keys', $keys);
	}
	return $keys['keys'];
}
