<?php

function kboo_asi_import_resource($res)
{
	//here's the meat.  must return an array containing node id and date of update.  check format of that date.
	//argument is a resource id from archive space.  not a node id
	//this operates on one resource

	$data = array();
	db_set_active('archive');
	//grab all the data we need from resource space db for this resource.

	db_set_active('default');
	return array($nid, $date);
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
