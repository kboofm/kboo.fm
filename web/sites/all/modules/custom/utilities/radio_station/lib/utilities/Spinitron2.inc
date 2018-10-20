<?php

#class SpinPapiException extends Exception {}


class Spinitron2 {

  /**
   * @var string What to do on SpinPapi error response. Set to:
   *   - 'notice' to trigger a PHP E_USER_NOTICE
   *   - 'throw' to throw a SpinPapiException
   *   - 'log:filepath' to log a message to the file at filepath
   */
  public $onError;


  /**
   * @var string A Spinitron station ID
   */
  public $station;


  /**
   * @var string A SpinPapi authentication user ID
   */
  public $userId;


  /**
   * @var string SpinPapi authentication secret
   */
  public $secret;


  /**
   * @var string|array Cache directory path or array of memcache servers
   */
  public $cache;


  /**
   * @var SpinPapiClient
   */
  private $client;


  /**
   * Construct a new SpinPapiData object.
   *
   * The SpinPapiClient object is not instantiated until it is used.
   *
   * @param string|array $config A file path to a config file or a configuration array.
   * @throws SpinPapiException on configuration error.
   */
  public function __construct($config) {
    if (is_string($config)) {
      if (!is_file($config) || !is_readable($config)) {
        throw new SpinPapiException("Invalid config file: {$config}");
      }

      $config = include($config);
    }

    foreach ($config as $key => $value) {
      if (!property_exists($this, $key)) {
        throw new SpinPapiException("Invalid config parameter: {$key}");
      }
      $this->$key = $value;
    }
  }


  /**
   * Returns the local SpinPapiClient object.
   *
   * Instantiates the local SpinPapiClient object if it does not exist.
   *
   * @return SpinPapiClient
   * @throws SpinPapiException on configuration error.
   */
  public function getClient() {
    if ($this->client === NULL) {
      include_once __DIR__ . '/SpinitronApiClient.php';
      $this->client = new SpinitronApiClient(
		$this->secret,
		$this->cache
      );

/*
      if ($this->cache) {
        if (is_string($this->cache)) {
          if (!is_dir($this->cache) || !is_writable($this->cache)) {
            throw new SpinPapiException(
              'Cache dir not found or not writable: ' . $this->cache
            );
          }

//          $this->client->fcInit($this->cache);
        } elseif (is_array($this->cache)) {
//          $this->client->mcInit($this->cache);
        } else {
          throw new SpinPapiException('Invalid cache config.');
        }

      } else {
        throw new SpinPapiException('Missing cache config.');
      }
*/
    }

    return $this->client;
  }


  /**
   * Runs the SpinPapi query and checks the response.
   *
   * @param $query
   * @return bool|array False on SpinPapi error response.
   * @throws SpinPapiException on error response if $this->onError is 'throw'
   */
  protected function runQuery($query, $fetch = false) {
    $endpoint = $query['method'];
    unset($query['endpoint']);

	if($fetch)
	{
		$response = $this->getClient()->fetch($endpoint, $query['id']);
	}
	else
	{
		$response = $this->getClient()->search($endpoint, $query);
	}

    if (!$fetch && isset($response['items'])) {
      return $response['items'];
    }
    else if($fetch)
    {
	return $response;
    }


    $message = 'SpinPapi error respose: ' . implode('. ', $response['errors']);
    if ($this->onError === 'notice') {
      trigger_error($message, E_USER_NOTICE);
    } elseif ($this->onError === 'throw') {
      throw new SpinPapiException($message);
    } elseif (strpos($this->onError, 'log:') === 0) {
      file_put_contents(
        substr($this->onError, 4),
        gmdate('Y-m-d\TH:i:s\Z ') . $message . "\n",
        FILE_APPEND
      );
    }

    return FALSE;
  }


  /**
   * Wrapper for SpinPapi getSong method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @param null $songId
   * @return array
   * @throws \SpinPapiException
   */
  public function getSong($songId = NULL) {
    return $this->runQuery(
      [
        'method' => 'getSong',
        'SongId' => $songId,
      ]
    );
  }


  /**
   * Wrapper for SpinPapi getSongs method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @param null $playlistId
   * @param int $num
   * @return array
   * @throws \SpinPapiException
   */
  public function getSongs($playlistId = NULL, $num = 99) {
	$parms = array('method' => 'spins');
	$parms['count'] = $num;
	if(!empty($playlistId))
	{
		$parms['playlist_id'] =  $playlistId;
	}
	return $this->runQuery($parms);
  }


  /**
   * Get current playlist id, then get that playlist's data
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @return array|bool
   * @throws \SpinPapiException
   */
  public function getCurrentPlaylist() {
    $current_id = $this->runQuery(
      [
        'method' => 'playlists',
	'end' => date(DATE_ISO8601),
      ]
    );

    return $this->getPlaylistInfo($current_id);
  }


  /**
   * Wrapper for SpinPapi getPlaylistInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @param null $playlistId
   * @return array
   * @throws \SpinPapiException
   */
  public function getPlaylistInfo($playlistId = NULL) {
    return $this->runQuery(
      [
        'method' => 'playlists',
        'id' => $playlistId,
      ], true
    );
  }


  /*
   * Wrapper for SpinPapi getPlaylistsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation

https://spinitron.github.io/v2api/#/ for api v2
all dates in new api are datetimes
YYYY-MM-DDTHH:MM:SS which is defined as DATE_ISO8601

   */
  public function getPlaylistsByDate($date, $count = 10, $showid = NULL, $ndays = NULL) {
	$start = '';
	if(isset($ndays))
	{
		$start = strtotime($date) - $ndays*24*60*60; 
		$start = date(DATE_ISO8601, $start);
	}
    $q = $this->runQuery(
      [
        'method' => 'playlists',
	'count' => $count,
        'end' => $date,
	'show_id' => $showid,
        'start' => $start,
      ]
    );
	usort($q, function($a, $b) {return ($a->start > $b->start) ? 1:-1;});
	return $q;
  }


  /*
   * Wrapper for SpinPapi getPlaylistsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   */
  public function getPlaylistsByShow($showId) {
    return $this->runQuery(
      [
        'method' => 'playlists',
        'UserID' => NULL,
        'ShowID' => $showId,
        'NDays' => NULL,
        'EndDate' => NULL,
        'Num' => 99,
      ], true
    );
  }


  /*
   * Wrapper for SpinPapi getPlaylistsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   */
  public function getPlaylistsByUser($userId) {
    return $this->runQuery(
      [
        'method' => 'getPlaylistsInfo',
        'UserID' => $userId,
        'ShowID' => NULL,
        'NDays' => NULL,
        'EndDate' => NULL,
        'Num' => 99,
      ]
    );
  }


  /**
   * Wrapper for SpinPapi getShowInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @param null $showId
   * @return array
   */
  public function getShowInfo($showId = NULL) {

    return $this->runQuery(
      [
        'id' => $showId,
	'method' => 'shows'
      ], true
    );
  }

  /**
   * Wrapper for SpinPapi getRegularShowsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @param string $when
   * @param null $startHour
   * @return array
   */
  public function getRegularShowsInfo($when = 'now', $startHour = NULL) {
    return $this->runQuery(
      [
        'method' => 'getRegularShowsInfo',
        'When' => $when,
        'StartHour' => $startHour,
      ]
    );
  }


  public static function instance() {
    $public_files = Helpers::getPublicFilesPath();
    $cache_path = "{$public_files}/spinitron/v2cache";
    $apikey = trim(file_get_contents(DRUPAL_ROOT . '/../spinitronv2apikey.txt'));

    return new Spinitron2(
	[
		'secret' => $apikey,
		'station' => 'kboo',
		'cache' => $cache_path,
        	'onError' => 'log:' . "{$cache_path}/spd.log",
	]
    );

  }
}
