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

    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $data = $processor->processRange(
      $result['node'],
      $start,
      $end
    );

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