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
    $playlistID = $playlist['PlaylistID'];
    $connection = RadioSpinitron2::getConnection();
    $playlist['Songs'] = $connection->getSongs($playlistID);
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


  public static function getLatestPlaylists($count) {
    $date = date("Y-m-d", time());

    $connection = RadioSpinitron2::getConnection();
    $playlists = $connection->getPlaylistsByDate($date, 7);

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

  public static function getLatestSongsTitles($count = null) {
    if (!$count) {
      $count = 99;
    }

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
		if(!array_key_exists($song['show_id'], $programs))
		{
			$show = $connection->getShowInfo($song['show_id']);

			$res = RadioSpinitron2::getProgNodeByTitle($show['title']);
			if(isset($res))
			{
				$programs[$song['show_id']] = array($show['title'], $res);
			}
		}
	}
#dpm($programs, 'programs');
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


  public static function getLatestSongs($count = null, $sort = NULL) {
    if (!$count) {
      $count = 99;
    }

    $connection = RadioSpinitron2::getConnection();
    $songs = $connection->getSongs(null, $count);
#dpm($songs, 'songs');
	usort($songs, 'RadioSpinitron2::sortSongsbyAirDate');
	//in spinitron api v2:
	//a "playlist" is an episode, matches to program by "show_id"
	//a show is a program
	//a spin is the actual thing played during an episode
	//$songs below is an array containing episodes ie spinitron playlists
	$programs = array();
	foreach($songs as $song)
	{
		if(!array_key_exists($song['show_id'], $programs))
		{
			$show = $connection->getShowInfo($song['show_id']);
#dpm($show, 'showinfo');
			$programs[$song['show_id']] = $show['title'];
		}
	}
#dpm($songs, 'songsorig');
	//need Artist, Title, Album, Date, Time
    $songs = array_map(
      function ($item) {
        $date = strtotime($item['start']); //format is YYYY-MM-DDTHH:MM:SS+OOOO
        $item['Date'] = date("m/j", $date);
        $item['Timestamp'] = date("g:ia", $date);
        $item['Time'] = date("g:ia", $date);
	$item['ShowID'] = $item['show_id'];
	$item['PlaylistID'] = $item['id'];
	$item['Title'] = $item['title'];
	$item['SongName'] = $item['title'];
	$item['Artist'] = 'test artist';
	$item['ArtistName'] = 'test artist';
	$item['Album'] = 'test album';
	$item['DiskName'] = 'test album';
        return $item;
      },
      $songs
    );
#dpm($songs, 'songsaltered');
	$active_prog = NULL;
	$dummy = array('SongID'=>'', 'Sequence'=>'', 'PlaylistID'=>'', 'ShowID'=>'', 'Date'=>'', 'Title'=>'', 'Album'=>'', 'Artist'=>'');
	$dummies = array();
	foreach($songs as $key=>$song)
	{
		if(is_null($active_prog) || $active_prog != $song['ShowID'])
		{
			$res = RadioSpinitron2::getProgNodeByTitle($programs[$song['ShowID']]);
			if(!empty($res))
			{
				$res = $res['node'];
				$res = current($res);
				$res = $res->nid;
				$dummies[] = array($key, $programs[$song['ShowID']], $song['ShowID'], $res);
				$songs[$key]['ProgramName'] = $programs[$song['ShowID']];
			}
		}
		$active_prog = $song['ShowID'];
	}
	foreach($dummies as $k => $dumbspot)
	{
		$dummy['thisprog'] = $dumbspot[1];
		$dummy['thisprogid'] = $dumbspot[2];
		$dummy['thisprognid'] = $dumbspot[3];
		array_splice($songs, $dumbspot[0]+$k, 0, array($dummy));
	}
#dpm($songs, 'songstoreturn');
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
    $date = date('Y-m-d', $field_air_time['value']);
    $playlists = $connection->getPlaylistsByDate($date);

    if (!$playlists) {
      return [];
    }

    // Filter out any playlists that occur outside of $field_air_time
    $playlists = array_filter(
      $playlists,
      function ($item) use ($field_air_time) {
        $start = $field_air_time['value'];
        $end = $field_air_time['value2'];

        $onair = "{$item['PlaylistDate']} {$item['OnairTime']}";
        $onair = strtotime($onair);

        $offair = "{$item['PlaylistDate']} {$item['OffairTime']}";
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
