<?php

class RadioAssets {
  private $current_route;
  private $routes;
  private $theme_path;

  public function __construct() {
    $this->current_route = current_path();
    $this->theme_path = drupal_get_path('theme', 'kbooui');

    $this->routes = [
      [
        'path' => 'programs/playlists',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeProgramsPlaylists'],
      ],
      [
        'path' => 'listen-now',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeListenNow'],
      ],
      [
        'path' => 'schedule',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeSchedule'],
      ],
    ];
  }


  private function matchSearchRoutes($search_type) {
    $routes = array_filter(
      $this->routes,
      function ($item) use ($search_type) {
        if ($item['search_type'] == $search_type) {
          return $item;
        }

        return false;
      }
    );

    return $routes;
  }


  private function checkEquals() {
    $routes = $this->matchSearchRoutes(EStringSearchOptions::Equals);

    array_walk(
      $routes,
      function ($item) {
        if ($item['path'] == $this->current_route) {
          call_user_func($item['callback']);
        }
      }
    );
  }



  private function checkStartswith() {
    $routes = $this->matchSearchRoutes(EStringSearchOptions::StartsWith);

    array_walk(
      $routes,
      function ($item) {
        if (Helpers::startsWith($this->current_route, $item['path'])) {
          call_user_func($item['callback']);
        }
      }
    );
  }


  public function add() {
    $this->checkEquals();
    $this->checkStartswith();
  }


  private function routeProgramsPlaylists() {
    $this->addDatePicker();
    $this->addJs("js/compiled/custom/station/playlists.js");
  }


  private function routeListenNow() {
    $this->addJPlayer();
    $this->addJs("js/compiled/custom/player/live-player.js");
  }


  private function routeSchedule() {
    $this->addJs("js/compiled/custom/station/carousel.js");
  }


  public function audioPlayer() {
    $this->addJPlayer();
    $this->addJs("js/compiled/custom/player/audio-player.js");
  }


  private function addDatePicker() {
    $dist = "bower_components/bootstrap-datepicker/dist";
    $this->addCss("{$dist}/css/bootstrap-datepicker3.min.css");
    $this->addJs("{$dist}/js/bootstrap-datepicker.min.js");
  }


  private function addJPlayer() {
    $dist = "bower_components/jPlayer/dist";
    $this->addCss("{$dist}/skin/blue.monday/css/jplayer.blue.monday.css");
    $this->addJs("{$dist}/jplayer/jquery.jplayer.min.js");
  }


  private function addCss($filepath) {
    drupal_add_css(
      "{$this->theme_path}/{$filepath}",
      [
        'type' => 'file',
        'weight' => 9999,
        'group' => CSS_THEME,
      ]
    );
  }


  private function addJs($filepath) {
    drupal_add_js(
      "{$this->theme_path}/{$filepath}",
      [
        'type' => 'file',
        'weight' => 9999,
        'group' => JS_THEME,
      ]
    );
  }
}
