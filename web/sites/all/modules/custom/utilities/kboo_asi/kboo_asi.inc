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
	$n->title = $res_rdata['Item Title'];
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

	$n->body['und'][0]['value'] = $res_rdata['Written notes on casing'];
	$n->body['en'][0]['value'] = $res_rdata['Written notes on casing'];


	$files = kboo_asi_get_files($ref);

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

	node_submit($n);
	node_save($n);
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

	return array($n->nid, date('Y-m-d H:i:s'));
}

function kboo_asi_program_lookup($progname)
{
#dpm($progname, 'progname');
	$q = db_query("select * from node where type='program' and title like :s", array(':s' => $progname));
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
		$n->title = $progname;
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
		$n->field_program_status['und'][0]['value'] = 0; //current
		$n->field_substitute['und'][0]['value'] = 0;
		$n->title_field['en'][0] = array(
			'value' => $progname,
			'format' => null,
			'safe_value' => $progname,
		);
		$n->title_original = $progname;
		node_submit($n);
#dpm($n, 'submitted program node');
		node_save($n);
		return $n->nid;
	}

}

function kboo_asi_host_lookup($hostname)
{
	$q = db_query("select * from node where type='person_profile' and title like :s", array(':s' => $hostname));
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
		$n->title = $hostname;
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
		$n->field_show_host_status['und'][0]['value'] = 1;
		$n->field_substitute['und'][0]['value'] = 0;
		$n->title_field['en'][0] = array(
			'value' => $hostname,
			'format' => null,
			'safe_value' => $hostname,
		);
		$n->title_original = $hostname;
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
		$files[] = $r->file_name;
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
