<?php

class RadioSpinitron2 {
  private static $connect;

  private static function getConnection() {
    if (!RadioSpinitron2::$connect) {
      RadioSpinitron2::$connect = Spinitron2::instance();
    }
    return RadioSpinitron2::$connect;
  }


  private static function includeSongs(&$playlist) {
    $playlistID = $playlist['id'];
    $connection = RadioSpinitron2::getConnection();
    $playlist['Songs'] = $connection->getSongs($playlistID);
	usort($playlist['Songs'], function($a, $b){return ($a['start'] > $b['start']) ? 1:-1;});
  }


  /**
   * Get current playlist
   *
   * @return array|bool
   */
  public static function getCurrentPlaylist() {
    $connection = RadioSpinitron2::getConnection();
    $playlist =  $connection->getCurrentPlaylist();
    RadioSpinitron2::includeSongs($playlist);
    return $playlist;
  }


  public static function getLatestPlaylists($count = 10) {
/*
print_r('<pre>');
print_r($count);
print_r($date);
print_r('</pre>');
*/
    $date = date(DATE_ISO8601);

    $connection = RadioSpinitron2::getConnection();
    $playlists = $connection->getPlaylistsByDate($date, $count);

#print_r('<pre>');
#print_r($date);
#print_r('</pre>');
    if (!$playlists) {
      return [];
    }

    return array_slice($playlists, 0, $count);
  }


  public static function getProgNodeByTitle($title)
  {
	#this is a workaround for titles like "Swing 'n Country" that are in spinitron as 'Swing & Country"
	$srch = trim($title);
	$nq = new NodeQuery();
	$nq->EntityCondition('bundle', 'program');
	$nq->SearchTitle($srch);
	$res = $nq->execute();
	while(!isset($res['node']) && strlen($srch) > 0)
	{
		$srch = explode(' ', $srch);
		array_pop($srch);
		$srch = implode(' ', $srch);
		$nq = new NodeQuery();
		$nq->EntityCondition('bundle', 'program');
		$nq->SearchTitle($srch);
		$res = $nq->execute();
	}
	if(isset($res['node']))
	{
		$res = $res['node'];
		$res = current($res);
		$res = $res->nid;
		return $res;
	}
	return NULL;
  }

  public static function getLatestSongsTitles($count = 99) {

	$connection = RadioSpinitron2::getConnection();
	$songs = $connection->getSongs(null, $count);
	usort($songs, 'RadioSpinitron2::sortSongsbyAirDate');
	//in spinitron api v2:
	//a "playlist" is an episode, matches to program by "show_id"
	//a show is a program
	//a spin is the actual thing played during an episode
	$programs = array();
	foreach($songs as $song)
	{
		$pl = $connection->getPlayListInfo($song['playlist_id']);
		if(!array_key_exists($pl['show_id'], $programs))
		{
			$show = $connection->getShowInfo($pl['show_id']);
			$prognid = RadioSpinitron2::getProgNodeByTitle($show['title']);
			$programs[$pl['show_id']] = array($show['title'], $show, $prognid);
		}
	}
	return $programs;
  }

  public static function sortSongsbyAirDate($songa, $songb)
  {
	if($songa['start'] == $songb['start'])
	{
		return 0;
	}
	return $songa['start'] < $songb['start'] ? -1 : 1;
  }


  public static function getLatestSongs($count = 99, $sort = NULL) {
	//ie spins
	$date = date(DATE_ISO8601);
	$connection = RadioSpinitron2::getConnection();
	
	$songs = $connection->getSongs(null, $count);

	usort($songs, 'RadioSpinitron2::sortSongsbyAirDate');
	//in spinitron api v2:
	//a "playlist" is an episode, matches to program by "show_id"
	//a show is a program
	//a spin is the actual thing played during an episode

	//songs is spins.  a spin only has a playlist_id reference, so we have to indirectly
	//get to show_id to get the program name ie show & showid
	$programs = array();
	$pls = array(); //playlists
	foreach($songs as $k=>$song)
	{
		$pl = $connection->getPlayListInfo($song['playlist_id']);
		$show = $connection->getShowInfo($pl['show_id']);
		$songs[$k]['show_id'] = $pl['show_id'];
		$songs[$k]['show_title'] = $show['title'];
		if(!array_key_exists($pl['show_id'], $programs))
		{
			$programs[$pl['show_id']] = $show['title'];
		}
	}
	//need Artist, Title, Album, Date, Time
    $songs = array_map(
      function ($item) {
        $date = strtotime($item['start']); //format is DATE_ISO8601
        $item['Date'] = date("m/j", $date);
        $item['Timestamp'] = date("g:ia", $date);
        $item['Time'] = date("g:ia", $date);
	$item['ShowID'] = $item['show_id'];
	$item['Title'] = $item['song'];
	$item['SongName'] = $item['song'];
	$item['Artist'] = $item['artist'];
	$item['ArtistName'] = $item['artist'];
	$item['Album'] = $item['release'];
	$item['DiskName'] = $item['release'];
        return $item;
      },
      $songs
    );
	$active_prog = NULL;
	$dummy = array('SongID'=>'', 'Sequence'=>'', 'PlaylistID'=>'', 'ShowID'=>'', 'Date'=>'', 'Title'=>'', 'Album'=>'', 'Artist'=>'');
	$dummies = array();
	foreach($songs as $key=>$song)
	{
		if(is_null($active_prog) || $active_prog != $song['show_id'])
		{
			$res = RadioSpinitron2::getProgNodeByTitle($programs[$song['show_id']]);
			if(!empty($res))
			{
				#$res = $res['node'];
				#$res = current($res);
				#$res = $res->nid;
				$dummies[] = array($key, $programs[$song['show_id']], $song['show_id'], $res);
				$songs[$key]['show_title'] = $programs[$song['show_id']];
			}
		}
		$active_prog = $song['show_id'];
	}
	foreach($dummies as $k => $dumbspot)
	{
		$dummy['thisprog'] = $dumbspot[1];
		$dummy['thisprogid'] = $dumbspot[2];
		$dummy['thisprognid'] = $dumbspot[3];
		array_splice($songs, $dumbspot[0]+$k, 0, array($dummy));
	}
    return $songs;
  }


  public static function getPlaylistDay($timestamp) {
    $date = date('Y-m-d', $timestamp);
    $connection = RadioSpinitron2::getConnection();
    $playlists = $connection->getPlaylistsByDate($date);

    foreach ($playlists as &$playlist) {
      RadioSpinitron2::includeSongs($playlist);
    }

    return $playlists;
  }


  public static function getEpisodePlaylist($node) {
    $wrapped_node = entity_metadata_wrapper('node', $node);
    $field_air_time = $wrapped_node->field_air_time->value();

    $connection = RadioSpinitron2::getConnection();
    $date = date(DATE_ISO8601, $field_air_time['value']);
    $playlists = $connection->getPlaylistsByDate($date, 10);
#dpm($playlists, 'pl');

    if (!$playlists) {
      return [];
    }

    // Filter out any playlists that occur outside of $field_air_time
    $playlists = array_filter(
      $playlists,
      function ($item) use ($field_air_time) {
        $start = $field_air_time['value'];
        $end = $field_air_time['value2'];

        #$onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = "{$item['start']}";
        $onair = strtotime($onair);

        #$offair = "{$item['PlaylistDate']} {$item['OffairTime']}";
        $offair = "{$item['end']}";
        $offair = strtotime($offair);

        if ($offair < $onair) {
          // If offair is the next day, then playlist date will be one day off
          $offair = strtotime("+1 day", $offair);
        }

        return ($start >= $onair && $end <= $offair);
      }
    );


    foreach ($playlists as &$playlist) {
      RadioSpinitron2::includeSongs($playlist);
    }

    return $playlists;
  }


  /**
   * Get recent playlists for a program
   *
   * @param $program_nid
   * @return array|bool|null
   */
  public static function getProgramRecentPlaylists($program_nid) {
    $wrapped_node = entity_metadata_wrapper('node', $program_nid);

    if (!$wrapped_node) {
      return NULL;
    }

    $showId = $wrapped_node->field_spinitron_showid->value();

    if (!$showId) {
      return NULL;
    }

    $connection = RadioSpinitron2::getConnection();
    $playlists = $connection->getPlaylistsByShow($showId);

    foreach ($playlists as &$playlist) {
      RadioSpinitron2::includeSongs($playlist);
    }

    return $playlists;
  }


  /**
   * Get playlist for a program at a given time
   *
   * @param $program_nid
   * @param $timestamp
   * @return null|string
   */
  public static function getProgramPlaylistDay($program_nid, $timestamp) {
    $wrapped_node = entity_metadata_wrapper('node', $program_nid);

    if (!$wrapped_node) {
      return NULL;
    }

    $showId = $wrapped_node->field_spinitron_showid->value();

    if (!$showId) {
      return NULL;
    }

    $connection = RadioSpinitron2::getConnection();
    $date = date('Y-m-d', $timestamp);
    $playlists = $connection->getPlaylistsByDate($date);

    $playlists = array_filter(
      $playlists,
      function ($item) use ($showId, $timestamp) {
        $onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = strtotime($onair);
        $dayBegin = Helpers::dayBegin($timestamp);

        $isShow = ($item['ShowID'] == $showId);
        $inRange = ($dayBegin <= $onair);
        return ($isShow && $inRange);
      }
    );

    foreach ($playlists as &$playlist) {
      RadioSpinitron2::includeSongs($playlist);
    }

    return $playlists;
  }
}
