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
}

