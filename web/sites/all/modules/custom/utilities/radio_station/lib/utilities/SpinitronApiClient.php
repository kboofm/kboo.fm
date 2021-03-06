<?php

class SpinitronApiClient
{
    protected $apiBaseUrl = 'https://spinitron.com/api';

    /**
     * @var array Cache expiration time per endpoint
     */
    protected static $cacheTimeout = [
        'personas' => 900,
        'shows' => 900,
        'playlists' => 300,
        'spins' => 30,
/*
        'personas' => 1,
        'shows' => 1,
        'playlists' => 1,
        'spins' => 1,
*/
    ];

    private $apiKey;
    private $fileCachePath;

    public function __construct($apiKey, $fileCachePath)
    {
        $this->apiKey = $apiKey;
        if (!is_dir($fileCachePath)) {
            throw new \Exception('$fileCachePath is not a directory');
        }
        if (!is_writable($fileCachePath)) {
            throw new \Exception('$fileCachePath is not writable');
        }
        $this->fileCachePath = $fileCachePath;
    }

    /**
     * Request resources from an endpoint using search parameters.
     *
     * @see https://spinitron.github.io/v2api for search parameters
     *
     * @param string $endpoint e.g. 'spins', 'shows' ...
     * @param array $params e.g. ['playlist_id' => 1234, 'page' => 2]
     * @return array Response with an array of resources of the endpoint's type plus metadata
     * @throws \Exception
     */
    public function search($endpoint, $params)
    {
        $url = '/' . $endpoint;
        if (!empty($params)) {
            $url .= '?' . http_build_query($params);
        }

        return json_decode($this->queryCached($endpoint, $url), true);
    }

    /**
     * Request a resource from an endpoint using its ID
     *
     * @param string $endpoint e.g. 'shows', 'personas', ...
     * @param int $id e.g. 2344
     * @return array Response with one resource of the endpoint's type plus metadata
     * @throws \Exception
     */
    public function fetch($endpoint, $id)
    {
        $url = '/' . $endpoint . '/' . $id;

        return json_decode($this->queryCached($endpoint, $url), true);
    }

    /**
     * Query the API with the given URL, returning the response JSON document either from
     * the local file cache or from the API.
     *
     * @param string $endpoint e.g. 'spins', 'shows' ...
     * @param string $url
     * @return string JSON document
     * @throws \Exception
     */
    protected function queryCached($endpoint, $url)
    {
        $timeout = static::$cacheTimeout[$endpoint];
        $cacheFile = $this->fileCachePath . '/' . $timeout . $url;

        if (is_file($cacheFile) && filemtime($cacheFile) > time() - $timeout) {
            // Cache hit. Return the cache file content.
#dpm('in cache hit');
            return file_get_contents($cacheFile);
        }

        // Cache miss. Request resource from the API.
#dpm('cache miss');
        $response = $this->queryApi($url);

        if (!file_exists(dirname($cacheFile))) {
            mkdir(dirname($cacheFile), 0755, true);
        }
	chmod($cacheFile, 0664);
	file_put_contents($cacheFile, $response);
	chmod($cacheFile, 0664); #not sure whether this necessary.  No docs on whether f_p_c sets perms
/*
        if(file_put_contents($cacheFile, $response) === FALSE)
	{
		#log the value of response
		$err_path = '/var/www/vhosts/kboo.fm/web/sites/default/files/err_cache_response';
		$err_fh = fopen($err_path, 'a');
		fwrite($err_fh, print_r($cacheFile, TRUE) . "\n");
		fwrite($err_fh, print_r($response, TRUE) . "\n\n");
		fclose($err_fh);
	}
*/

        return $response;
    }

    /**
     * @param $url
     * @return string JSON document
     * @throws \Exception
     */
    protected function queryApi($url)
    {
        $context = stream_context_create([
            'http' => [
                'user_agent' => 'Mozilla/5.0 Spinitron v2 API demo client',
                'header' => 'Authorization: Bearer ' . $this->apiKey,
		'method' => 'GET',
            ],
        ]);
#dpm($url, 'url');
        $fullUrl = $this->apiBaseUrl . $url;
#dpm($fullUrl);
/*
	if(strpos($fullUrl, '?') === FALSE)
	{
		//then we're not doing a query...
		$fullUrl .= '?access-token=' . $this->apiKey;
	}
	else
	{
		$fullUrl .= '&access-token=' . $this->apiKey;
	}
*/

#dpm($fullUrl, 'fullurl');
//	$stream = drupal_http_request($fullUrl, ['headers'=>['header'=>'Authorization: Bearer ' . $this->apiKey, 'User-Agent'=>'Mozilla/5.0 Spinitron v2 API client']]);
	$c = curl_init();
	curl_setopt($c, CURLOPT_HTTPHEADER, array('Authorization: Bearer ' . $this->apiKey));
	curl_setopt($c, CURLOPT_USERAGENT, 'Mozilla/5.0 Spinitron v2 API client');
	curl_setopt($c, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($c, CURLOPT_URL, $fullUrl);
	$res = curl_exec($c);
	curl_close($c);
        if ($res === false) {
            throw new Exception('Error requesting ' . $fullUrl . ': cUrl call failed', true);
        }
	return $res;

	


/*
        $stream = fopen($fullUrl, 'rb', false, $context);
        if ($stream === false) {
            throw new Exception('Error opening stream for ' . $fullUrl . ' with context ' . $context);
        }

        $response = stream_get_contents($stream);
*/
        if ($response === false) {
            throw new Exception('Error requesting ' . $fullUrl . ': ' . var_export(stream_get_meta_data($stream), true));
        }

        return $response;
    }
}
