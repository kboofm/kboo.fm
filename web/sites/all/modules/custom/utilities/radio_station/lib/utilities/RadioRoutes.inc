<?php

class RadioRoutes {
  private $items;


  public function __construct() {
    $this->items = [];
  }


  public function get() {
    $this->adminRoutes();
    $this->apiRoutes();
    $this->pageRoutesPrivate();
    $this->pageRoutesPublic();
    return $this->items;
  }


  private function adminRoutes() {
  }


  private function apiRoutes() {
    $this->items['api/playlists'] = [
      'title' => 'Get playlists',
      'page callback' => 'radio_station_get_playlists',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/schedule/episode/%/%/%'] = [
      'title' => 'Get Episode',
      'page callback' => 'radio_station_get_episode',
      'page arguments' => [3, 4, 5],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/schedule/day/%/%/%'] = [
      'title' => 'Get Day',
      'page callback' => 'radio_station_get_day',
      'page arguments' => [3, 4, 5],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/schedule/week/%/%/%'] = [
      'title' => 'Get Week',
      'page callback' => 'radio_station_get_week',
      'page arguments' => [3, 4, 5],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];
  }


  private function pageRoutesPrivate() {
  }


  private function pageRoutesPublic() {
    $this->items['blog'] = [
      'title' => 'Blog',
      'page callback' => 'radio_station_get_blog',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['community-events'] = [
      'title' => 'Community Events',
      'page callback' => 'radio_station_get_community_events',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['news'] = [
      'title' => 'News',
      'page callback' => 'radio_station_get_news',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['programs/%/content'] = [
      'title callback' => 'radio_station_get_programs_content_title',
      'title arguments' => [1],
      'page callback' => 'radio_station_get_programs_content',
      'page arguments' => [1],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['programs/playlists'] = [
      'title' => 'Programs Playlists',
      'page callback' => 'radio_station_get_programs_playlists',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['schedule'] = [
      'title' => 'Weekly Schedule',
      'page callback' => 'radio_station_get_schedule',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];
  }
}
