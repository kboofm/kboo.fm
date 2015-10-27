<?php

class Spinitron {

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
      $this->client = new SpinPapiClient(
          $this->userId,
          $this->secret,
          $this->station,
          $this->onError === 'notice'
        );

      if ($this->cache) {
        if (is_string($this->cache)) {
          if (!is_dir($this->cache) || !is_writable($this->cache)) {
            throw new SpinPapiException(
              'Cache dir not found or not writable: ' . $this->cache
            );
          }

          $this->client->fcInit($this->cache);
        } elseif (is_array($this->cache)) {
          $this->client->mcInit($this->cache);
        } else {
          throw new SpinPapiException('Invalid cache config.');
        }

      } else {
        throw new SpinPapiException('Missing cache config.');
      }
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
  protected function runQuery($query) {
    $response = $this->getClient()->query($query);

    if ($response['success'] === TRUE) {
      return $response['results'];
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
  public function getSongs($playlistId = NULL, $num = 1) {
    return $this->runQuery(
      [
        'method' => 'getSongs',
        'PlaylistId' => $playlistId,
        'Num' => $num,
      ]
    );
  }


  /**
   * Wrapper for SpinPapi getCurrentPlaylist method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   *
   * @return array|bool
   * @throws \SpinPapiException
   */
  public function getCurrentPlaylist() {
    return $this->runQuery(
      [
        'method' => 'getCurrentPlaylist',
      ]
    );
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
        'method' => 'getPlaylistInfo',
        'PlaylistID' => $playlistId,
      ]
    );
  }


  /*
   * Wrapper for SpinPapi getPlaylistsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   */
  public function getPlaylistsByDate($endDate, $ndays = 1) {
    return $this->runQuery(
      [
        'method' => 'getPlaylistsInfo',
        'UserID' => NULL,
        'ShowID' => NULL,
        'NDays' => $ndays,
        'EndDate' => $endDate,
        'Num' => NULL,
      ]
    );
  }


  /*
   * Wrapper for SpinPapi getPlaylistsInfo method.
   *
   * @see SpinPapi API Specification https://bitbucket.org/spinitron/documentation
   */
  public function getPlaylistsByShow($showId) {
    return $this->runQuery(
      [
        'method' => 'getPlaylistsInfo',
        'UserID' => NULL,
        'ShowID' => $showId,
        'NDays' => NULL,
        'EndDate' => NULL,
        'Num' => 99,
      ]
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
        'method' => 'getShowInfo',
        'ShowID' => $showId,
      ]
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
    $wrapper = file_stream_wrapper_get_instance_by_uri('public://');
    $public_files = $wrapper->realpath();
    $cache_path = "{$public_files}/spinitron/cache";

    return new Spinitron(
      [
        'station' => 'kboo',
        'userId' => '',
        'secret' => '',

        // For a memcache, set to an array of one or more memcache servers,
        // see http://au1.php.net/manual/en/memcached.addservers.php
        'cache' => $cache_path,
        'onError' => 'log:' . "{$cache_path}/spd.log",
      ]
    );
  }
}
