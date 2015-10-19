<?php
require_once 'utilities/Helpers.inc';


class TemplateQuery {
  public static function scheduledNow() {
    $query = new ScheduledTimeslotQuery();
    $query->getNow();
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    $processor = new ScheduleProcessor();
    return $processor->processNow(
      $result['node']
    );
  }

  public static function scheduledNext($count = 1) {
    $now = time();
    $query = new ScheduledTimeslotQuery();
    $query->getNext($now, $count);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->process(
      $result['node'],
      time(),
      'after',
      $count
    );
  }


  public static function scheduledToday() {
    $start = Helpers::todayBegin();
    $end = Helpers::dayEnd($start);

    $query = new ScheduledTimeslotQuery();
    $query->getRange($start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processRange(
      $result['node'],
      $start,
      $end
    );
  }


  public static function scheduledThisWeek() {
    $now = time();
    $start = Helpers::weekBegin($now);
    $end = Helpers::weekEnd($now);

    $query = new ScheduledTimeslotQuery();
    $query->getRange($start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return [];
    }

    $processor = new ScheduleProcessor();
    return $processor->processRange(
      $result['node'],
      $start,
      $end,
      true
    );
  }
}
