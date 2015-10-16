<?php

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
    return $processor->processAfter(
      $result['node'],
      time(),
      $count
    );
  }


  public static function scheduledToday() {
    $now = time();

    $start = new DateTime("@{$now}");
    $start->setTime(0, 0, 0);
    $start = $start->getTimestamp();

    $end = new DateTime("@{$now}");
    $end->setTime(23, 59, 59);
    $end = $end->getTimestamp();

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

    $start = new DateTime("@{$now}");
    $start->modify("last Sunday");
    $start->setTime(0, 0, 0);
    $start = $start->getTimestamp();

    $end = new DateTime("@{$now}");
    $end->modify("next Saturday");
    $end->setTime(23, 59, 59);
    $end = $end->getTimestamp();

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


  public static function scheduledNextWeek() {
    $now = time();

    $start = new DateTime("@{$now}");
    $start->modify("next Sunday");
    $start->setTime(0, 0, 0);
    $start = $start->getTimestamp();

    $end = new DateTime("@{$start}");
    $end->modify("+1 week");
    $end->setTime(23, 59, 59);
    $end = $end->getTimestamp();

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
