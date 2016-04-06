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

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();

    $when = ($direction == 'prev') ? 'before' : 'after';
    $data = $processor->process(
      $result['node'],
      $timestamp,
      $when
    );

    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getDay($stream, $direction, $timestamp) {
    $component = new ScheduleComponent();
    $data = $component->getDay($stream, $direction, $timestamp);
    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getWeek($stream, $direction, $timestamp) {
    $component = new ScheduleComponent();
    $data = $component->getWeek($stream, $direction, $timestamp);
    $this->addTemplateData($data);
    $this->renderJson();
  }
}