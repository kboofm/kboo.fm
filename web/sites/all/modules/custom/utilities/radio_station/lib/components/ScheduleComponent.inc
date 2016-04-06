<?php

class ScheduleComponent extends BaseComponent {
  public function now($stream) {
    $query = new ScheduledTimeslotQuery();
    $query->getNow($stream);
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();
    return $processor->processNow(
      $this->getNodes($result)
    );
  }


  public function next($stream, $count = 1) {
    $now = time();
    $query = new ScheduledTimeslotQuery();
    $query->getNext($stream, $now, $count);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->process(
      $this->getNodes($result),
      time(),
      'after',
      $count
    );
  }


  public function today($stream) {
    $start = Helpers::todayBegin();
    $end = Helpers::dayEnd($start);

    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processRange(
      $this->getNodes($result),
      $start,
      $end
    );
  }


  public function thisWeek($stream) {
    $now = time();
    $start = Helpers::weekBegin($now);
    $end = Helpers::weekEnd($now);

    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processRange(
      $this->getNodes($result),
      $start,
      $end,
      true
    );
  }


  public function calendarWeek($stream) {
    $now = time();
    $start = Helpers::weekBegin($now);
    $end = Helpers::weekEnd($now);

    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processRangeCalendar(
      $this->getNodes($result),
      $start,
      $end
    );
  }


  public function getTimeslotsForProgram($program_nid) {
    $query = new ScheduledTimeslotQuery();
    $query->getForProgram($program_nid);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processForProgram(
      $this->getNodes($result)
    );
  }

  public function getWeek($stream, $direction, $timestamp) {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $cache_key = "radio_station_week_{$stream}_{$timestamp}";

      if ($cache = cache_get($cache_key)) {
        $data = $cache->data;
      } else {
        $data = $this->loadWeek($stream, $direction, $timestamp);
        cache_set($cache_key, $data, 'cache');
      }
    }

    return $data;
  }


  private function loadWeek($stream, $direction, $timestamp) {
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
    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();

    $data = $processor->processRange(
      $result['node'],
      $start,
      $end,
      true
    );

    return $data;
  }
}

