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
    return $processor->processFirst(
      $result['node']
    );
  }
}
