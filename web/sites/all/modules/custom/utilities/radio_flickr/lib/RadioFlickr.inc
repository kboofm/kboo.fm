<?php

class RadioFlickr {
  private $flickr_endpoint;
  private $flickr_parameters;
  private $flickr_url;
  private $url_type;


  public function __construct() {
    $this->url_type = 'url_m';

    $this->flickr_parameters = [
      //Comment ported from Drupal 6 codebase
      // DEV KEY: THIS IS ONLY A DEV KEY IT SHOULD BE REPLACED WITH A NEW KEY
      'api_key' => '8b81329bafce2de6ab39437eec9a7cf0',

      'method' => 'flickr.photosets.getPhotos',
      'photoset_id' => null,
      'extras' => $this->url_type,
      'format' => 'php_serial',
    ];

    $this->flickr_endpoint = "https://api.flickr.com/services/rest";
    $this->flickr_url = "http://www.flickr.com/photos";
  }


  public function getGallery($id) {
    $request_endpoint = $this->getRequestEndpoint($id);
    $response = $this->processRequest($request_endpoint);
    return $response;
  }


  private function processRequest($endpoint) {
    $rsp = unserialize(
      file_get_contents($endpoint)
    );

    if (!$rsp['stat'] == 'ok') {
      return [];
    }

    $owner = $rsp['photoset']['owner'];

    $photos = array_map(
      function ($item) use ($owner) {
        if ($item['height_m'] > $item['width_m']) {
          return null;
        }

        $url = "{$this->flickr_url}/{$owner}/{$item['id']}/sizes";

        return [
          'url' => $url,
          'image' => $item[$this->url_type],
          'alt' => $item['title'],
          'caption' => $item['title'],
        ];
      },
      $rsp['photoset']['photo']
    );

    // Remove null elements
    $photos = array_filter($photos);
    return $photos;
  }


  private function getRequestEndpoint($id) {
    $params = $this->flickr_parameters;
    $params['photoset_id'] = $id;

    array_walk(
      $params,
      function (&$value, $key) {
        $value = urlencode($key) . "=" . urlencode($value);
      }
    );

    $params = array_values($params);
    $params = implode('&', $params);

    $endpoint = "{$this->flickr_endpoint}?{$params}";
    return $endpoint;
  }
}
