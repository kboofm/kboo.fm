<?php

class TileComponent extends BaseComponent {
  public function blogPosts($count) {
    $more_link = "blog";

    $query = new BlogPostQuery();
    $query->getLatestByShowHosts();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new TeaserTileProcessor();
    return $processor->process(
      $this->getNodes($result),
      'Show Host Blog',
      $more_link
    );
  }


  public function takinItToTheStreets($count) {
    $more_link = "new-orleans-community/inthestreet";

    $query = new TakinItToTheStreetsQuery();
    $result = $query->execute();
    $nodes = $this->getNodes($result);

    $query = new EventQuery();
    $query->getLatestTakingItToTheStreets();

    // Reduce count by one to account for the single node above
    $query->setLimit($count - 1);

    $result = $query->execute();
    $nodes = $nodes + $this->getNodes($result);

    $processor = new TeaserTileProcessor();
    return $processor->process(
      $nodes,
      "Takin' it to the Streets",
      $more_link
    );
  }


  public function latestMedia($count) {
    $more_link = "news";

    $query = new HasMediaQuery();
    $query->getLatest();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new TeaserTileProcessor();
    return $processor->process(
      $this->getNodes($result),
      'Latest Media',
      $more_link
    );
  }


  public function cuttinClass($count) {
    $more_link = "programs/cuttin-class";

    $query = new TitleQuery();
    $query->getLatest("Cuttin' Class", true);
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new TeaserTileProcessor();
    return $processor->process(
      $this->getNodes($result),
      "Cuttin' Class",
      $more_link
    );
  }


  public function support() {
    $more_link = "support";

    return [
      'type' => 'content',
      'heading' => "Support 'OZ",
      'more_link' => $more_link,
      'image' => 'sites/all/themes/custom/wwozui/images/photos/support-oz-group.jpg',
      'url' => "/support/2015-fall-membership-drive-highlights-thanks-day11",
      'title' => [
        'icon' => TRUE,
        'text' => "Photo highlights from our Fall 2015 Membership Drive",
      ],
      'list' => [
        [
          'icon' => FALSE,
          'title' => 'Why support WWOZ?',
          'url' => '/blog/228333',
        ],
        [
          'icon' => FALSE,
          'title' => "Find out how easy it is to donate a car",
          'url' => '/support/car-donations',
        ],
      ],
    ];
  }


  public function programming() {
    $more_link = "programs";

    return [
      'type' => 'content',
      'heading' => "Programming",
      'more_link' => $more_link,
      'image' => 'sites/all/themes/custom/wwozui/images/photos/programming-KeithHill.png',
      'url' => "/programs/show-hosts",
      'title' => [
        'icon' => FALSE,
        'text' => "Show Hosts",
      ],
      'list' => [
        [
          'icon' => FALSE,
          'title' => 'Program Schedule',
          'url' => '/schedule',
        ],
        [
          'icon' => FALSE,
          'title' => "WWOZ Podcasts",
          'url' => '/programs/wwoz-podcasts',
        ],
      ],
    ];
  }


  public function streamingAudio() {
    $heading = 'Listen Now';
    $more_link = "programs/streams";

    $lead_title = "Tune in live to 'OZ's primary stream";
    $lead_url = '/listen/player/';
    $lead_image_url = 'sites/all/themes/custom/wwozui/images/photos/two-week-stream.jpg';

    $stream1_title = "Or tune in to Radio's second stream";
    $stream1_url = '/listen/player?stream=stream2';

    $stream2_title = 'Listen to the 2-week stream archive';
    $stream2_url = '/listen/archive/';

    $list = [
      [
        'icon' => TRUE,
        'title' => $stream1_title,
        'url' => $stream1_url,
      ],
      [
        'icon' => TRUE,
        'title' => $stream2_title,
        'url' => $stream2_url,
      ],
    ];

    $tile = [
      'url' => $lead_url,
      'type' => 'content',
      'heading' => $heading,
      'more_link' => $more_link,
      'image' => $lead_image_url,
      'title' => [
        'icon' => TRUE,
        'text' => $lead_title,
      ],
      'list' => $list,
    ];

    return $tile;
  }
}
