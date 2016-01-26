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
    $this->items['admin/config/content/livewire-hotline'] = [
      'title' => 'Station Livewire & Hotline',
      'description' => 'Configuration for Livewire & Hotline',
      'page callback' => 'drupal_get_form',
      'page arguments' => ['radio_station_livewire_form'],
      'access callback' => 'radio_station_user_has_role',
      'access arguments' => [
        [
          'Livewire Reader',
          'Admin - Station',
          'Admin - Site Administrator',
        ]
      ],
      'type' => MENU_NORMAL_ITEM,
    ];
  }


  private function apiRoutes() {
    $this->items['api/acts'] = [
      'title' => 'Acts',
      'page callback' => 'radio_station_acts',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/player/carousel'] = [
      'title' => 'Player Carousel',
      'page callback' => 'radio_station_player_carousel',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/playlists'] = [
      'title' => 'Get playlists',
      'page callback' => 'radio_station_get_playlists',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/promos/%'] = [
      'title' => 'Promos',
      'page callback' => 'radio_station_promos',
      'page arguments' => [2],
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['api/samples/groove-guardian/%'] = [
      'title' => 'Sample Ads',
      'page callback' => 'radio_station_sample_groove_guardian',
      'page arguments' => [3],
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

    $this->items['api/venue'] = [
      'title' => 'Acts',
      'page callback' => 'radio_station_venue',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];
  }


  private function pageRoutesPrivate() {
    $this->items['station/livewire-hotline'] = [
      'title' => 'Station Livewire & Hotline',
      'page callback' => 'radio_station_get_livewire_generator',
      'access callback' => 'radio_station_user_has_role',
      'access arguments' => [
        [
          'Livewire Reader',
          'Admin - Station',
          'Admin - Site Administrator',
        ]
      ],
      'type' => MENU_CALLBACK,
    ];

    $this->items['station/events/quick/add'] = [
      'title' => 'Quickly add multiple events',
      'page callback' => 'radio_station_get_events_quick_add',
      'access callback' => 'radio_station_user_has_role',
      'access arguments' => [
        [
          'Manager - Calendar',
          'Admin - Site Administrator',
          'Admin - Developer',
        ]
      ],
      'type' => MENU_CALLBACK,
    ];

    $this->items['station/events/quick/view'] = [
      'title' => 'Quickly view recently added events',
      'page callback' => 'radio_station_get_events_quick_view',
      'access callback' => 'radio_station_user_has_role',
      'access arguments' => [
        [
          'Manager - Calendar',
          'Admin - Site Administrator',
          'Admin - Developer',
        ]
      ],
      'type' => MENU_CALLBACK,
    ];
  }


  private function pageRoutesPublic() {
    $this->items['about/contributors'] = [
      'title' => 'WWOZ Contributors',
      'page callback' => 'radio_station_get_about_contributors',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['blog'] = [
      'title' => 'WWOZ Blog',
      'page callback' => 'radio_station_get_blog',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['community-events'] = [
      'title' => 'Upcoming Community Events in the New Orleans Area',
      'page callback' => 'radio_station_get_community_events',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['livewire'] = [
      'title' => 'Livewire Music Calendar',
      'page callback' => 'radio_station_get_livewire_calendar',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['live-events'] = [
      'title' => 'WWOZ Live Event Broadcasts',
      'page callback' => 'radio_station_get_live_events',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['live-events/previous'] = [
      'title' => 'WWOZ Live Event Broadcasts',
      'page callback' => 'radio_station_get_live_events_previous',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['news'] = [
      'title' => 'New Orleans Articles & Announcements',
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

    $this->items['programs/%/podcast'] = [
      'title callback' => 'radio_station_get_programs_podcast_title',
      'title arguments' => [1],
      'page callback' => 'radio_station_get_programs_podcast',
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

    $this->items['programs/show-hosts'] = [
      'title' => 'WWOZ Show Hosts',
      'page callback' => 'radio_station_get_programs_show_hosts',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['programs/streams'] = [
      'title' => 'Listen to WWOZ From Anywhere!',
      'page callback' => 'radio_station_get_programs_streams',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['schedule'] = [
      'title' => 'WWOZ New Orleans 90.7FM Weekly Schedule',
      'page callback' => 'radio_station_get_schedule',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];

    $this->items['venues'] = [
      'title' => 'New Orleans Area Music Venues',
      'page callback' => 'radio_station_get_venues',
      'access arguments' => ['access content'],
      'type' => MENU_CALLBACK,
    ];
  }
}
