<?php

class TemplateQuery {
  public static function scheduledNow() {
    $query = new ScheduledTimeslotQuery();
    $query->getNow();
    $result = $query->execute();

    $processor = new ScheduleProcessor();
    return $processor->process(
      $result['node']
    );
  }
}
