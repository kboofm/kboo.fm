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
    $this->items['admin/config/station'] = [
      'title' => 'Station',
      'description' => 'Settings related to the station.',
      'position' => 'right',
      'weight' => -15,
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => ['access administration pages'],
      'file' => 'system.admin.inc',
      'file path' => drupal_get_path('module', 'system'),
    ];

    $this->items['admin/config/station/streams'] = [
      'title' => "Streams",
      'description' => "Configuration for Streams",
      'page callback' => 'drupal_get_form',
      'page arguments' => ['radio_station_streams_form'],
      'access callback' => 'radio_station_user_has_role',
      'access arguments' => [
        [
          'Admin - Site Administrator',
        ]
      ],
      'type' => MENU_NORMAL_ITEM,
    ];
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

    $this->items['home'] = [
      'title' => 'Home',
      'page callback' => 'radio_station_get_home',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['listen-now'] = [
      'title' => 'Listen Now',
      'page callback' => 'radio_station_get_listen_now',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['news'] = [
      'title' => 'News',
      'page callback' => 'radio_station_get_news',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['program/%/content'] = [
      'title callback' => 'radio_station_get_program_content_title',
      'title arguments' => [1],
      'page callback' => 'radio_station_get_program_content',
      'page arguments' => [1],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['program/playlists'] = [
      'title' => 'Program Playlists',
      'page callback' => 'radio_station_get_program_playlists',
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
