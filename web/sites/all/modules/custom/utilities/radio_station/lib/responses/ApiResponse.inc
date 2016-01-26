<?php

class ApiResponse extends Response {

  public function getEpisode($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $query->getAt($stream, $timestamp);
        break;
      case 'prev':
        $query->getPrevious($stream, $timestamp);
        break;
      case 'next':
        $query->getNext($stream, $timestamp);
        break;
      default:
        return NULL;
    }

    $result = $query->execute();

    $processed = $this->processResponse(
      $result,
      $direction,
      $timestamp
    );

    if (!$processed) {
      $processed = [];
    }

    $this->addTemplateData($processed);
    $this->renderJson();
  }


  public function getDay($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $start = Helpers::dayBegin($timestamp);
        break;
      case 'prev':
        $start = Helpers::dayBeforeBegin($timestamp);
        break;
      case 'next':
        $start = Helpers::dayAfterBegin($timestamp);
        break;
      default:
        return NULL;
    }

    $end = Helpers::dayEnd($start);
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    $processed = $this->processRangeResponse(
      $result,
      $start,
      $end
    );

    $this->addTemplateData($processed);
    $this->renderJson();
  }


  public function getWeek($stream, $direction, $timestamp) {
    $query = new ScheduledTimeslotQuery();

    switch ($direction) {
      case 'at':
        $start = Helpers::weekBegin($timestamp);
        break;
      case 'prev':
        $start = Helpers::weekBeforeBegin($timestamp);
        break;
      case 'next':
        $start = Helpers::weekAfterBegin($timestamp);
        break;
      default:
        return NULL;
    }

    $end = Helpers::weekEnd($start);
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    $processed = $this->processRangeResponse(
      $result,
      $start,
      $end,
      true
    );

    $this->addTemplateData($processed);
    $this->renderJson();
  }


  public function getSampleAds($style) {
    $redirect_url = "https://www.wwoz.org";
    $path = drupal_get_path('theme', 'wwozui');
    $path .= "/images/sponsors";
    $filename = 'groove-guardian-280x120.png';

    $this->addTemplateData([
      [
        'redirect_url' => $redirect_url,
        'path' => file_create_url("{$path}/{$filename}"),
      ]
    ]);
    $this->renderJson();
  }


  public function getPlayerCarousel() {
    $jsonfile = drupal_realpath('public://') . "/listen/player/carousel.json";
    $data = json_decode(
      file_get_contents($jsonfile)
    );
    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getPromos($count) {
    $query = new PromoteLatestQuery();
    $query->getLatest();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new PlayerCarouselProcessor();
    $processed = $processor->process(
      $result['node']
    );

    $this->addTemplateData($processed);
    $this->renderJson();
  }


  public function getActs($startswith) {
    $component = new ActComponent();
    $data = $component->getSelect2($startswith);
    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getVenue($startswith) {
    $component = new OrganizationComponent();
    $data = $component->getSelect2($startswith);
    $this->addTemplateData($data);
    $this->renderJson();
  }


  private function processRangeResponse($result, $start, $end, $groupByDay = false) {
    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $data = $processor->processRange(
      $result['node'],
      $start,
      $end,
      $groupByDay
    );

    return $data;
  }


  private function processResponse($result, $direction, $timestamp) {
    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $when = ($direction == 'prev') ? 'before' : 'after';
    $data = $processor->process(
      $result['node'],
      $timestamp,
      $when
    );

    return $data;
  }
}