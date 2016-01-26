<?php

class RadioAssets {
  private $current_route;
  private $routes;
  private $theme_path;

  public function __construct() {
    $this->current_route = current_path();
    $this->theme_path = drupal_get_path('theme', 'wwozui');

    $this->routes = [
      [
        'path' => 'livewire',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeLivewire'],
      ],
      [
        'path' => 'programs/playlists',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeProgramsPlaylists'],
      ],
      [
        'path' => 'programs/streams',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeProgramsStreams'],
      ],
      [
        'path' => 'station/events/quick/add',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeEventsQuickadd'],
      ],
      [
        'path' => 'station/livewire-hotline',
        'search_type' => EStringSearchOptions::Equals,
        'callback' => [$this, 'routeLivewireHotline'],
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


  private function routeLivewire() {
    $this->addDatePicker();
    $this->addJs("js/compiled/custom/station/livewire-calendar.js");
  }



  private function routeEventsQuickadd() {
    $this->addDateTimePicker();
    $this->addSelect2();
    $this->addJs("js/compiled/custom/station/events-quickadd.js");
  }


  private function routeLivewireHotline()
  {
    $params = Helpers::getQueryParameters();

    $phase = isset($params['phase']) ?
      $params['phase'] : ELivewireRoutePhase::EventForm;

    if ($phase == ELivewireRoutePhase::EventForm) {
      $this->addDatePicker();
      $this->addJs("js/compiled/custom/station/livewire-events.js");

    } elseif ($phase == ELivewireRoutePhase::ScriptForm) {
      $this->addJs("js/compiled/custom/station/livewire-script.js");
    }
  }


  private function routeProgramsPlaylists() {
    $this->addDatePicker();
    $this->addJs("js/compiled/custom/station/playlists.js");
  }


  private function routeProgramsStreams() {
    $this->addModals();
  }


  private function routeSchedule() {
    $this->addJs("js/compiled/custom/station/carousel.js");
  }


  public function audioPlayer() {
    $dist = "bower_components/jPlayer/dist";
    $this->addCss("{$dist}/skin/blue.monday/css/jplayer.blue.monday.css");
    $this->addJs("{$dist}/jplayer/jquery.jplayer.min.js");
    $this->addJs("js/compiled/custom/player/audio-player.js");
  }


  private function addDatePicker() {
    $dist = "bower_components/bootstrap-datepicker/dist";
    $this->addCss("{$dist}/css/bootstrap-datepicker3.min.css");
    $this->addJs("{$dist}/js/bootstrap-datepicker.min.js");
  }


  private function addDateTimePicker() {
    $this->addMoment();

    $dist = "bower_components/eonasdan-bootstrap-datetimepicker/build";
    $this->addCss("{$dist}/css/bootstrap-datetimepicker.min.css");
    $this->addJs("{$dist}/js/bootstrap-datetimepicker.min.js");
  }


  private function addMoment() {
    $dist = "bower_components/moment";
    $this->addJs("{$dist}/min/moment.min.js");
  }


  private function addSelect2() {
    $dist = "bower_components/select2";
    $this->addCss("{$dist}/select2.css");
    $this->addJs("{$dist}/select2.js");

    $dist = "bower_components/select2-bootstrap-css";
    $this->addCss("{$dist}/select2-bootstrap.css");
  }


  private function addModals() {
    $this->addJs("bower_components/bootstrap/js/modal.js");
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
