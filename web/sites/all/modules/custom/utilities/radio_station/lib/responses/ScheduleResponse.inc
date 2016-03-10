<?php

class ScheduleResponse extends Response {

  private function getOnAir($stream) {
    $component = new ScheduleComponent();
    $schedule_item = $component->now($stream);

    $data = null;
    if ($schedule_item) {
      $data = [$schedule_item];
    }

    $onair = [
      'data' => $data,
      'timestamp' => $schedule_item['start']['timestamp'],
      'type' => 'episode-now',
      'stream' => $stream,
    ];

    return $onair;
  }


  private function getShows($stream) {
    $component = new ScheduleComponent();
    $data = $component->next($stream);

    $timestamp = null;
    $datetime = null;

    if (isset($data[0]['start']['timestamp'])) {
      $start = $data[0]['start'];
      $timestamp = $start['timestamp'];
      $datetime = $start['formatted_date'] . ' ' . $start['formatted_time'];
    }

    $scheduled_shows = [
      'id' => 'schedule-episode',
      'type' => 'episode',
      'data' => $data,
      'stream' => $stream,
      'timestamp' => $timestamp,
      'datetime' => $datetime,
    ];

    return $scheduled_shows;
  }


  private function getDay($stream) {
    $component = new ScheduleComponent();
    $data = $component->today($stream);

    $timestamp = null;
    $datetime = null;

    if (isset($data[0]['start']['timestamp'])) {
      $start = $data[0]['start'];
      $timestamp = $start['timestamp'];
      $datetime = $start['formatted_date'];
    }

    $scheduled_day = [
      'id' => 'schedule-day',
      'type' => 'day',
      'stream' => $stream,
      'data' => $data,
      'timestamp' => $timestamp,
      'datetime' => $datetime,
    ];

    return $scheduled_day;
  }


  private function getWeek($stream) {
    $component = new ScheduleComponent();
    $data = $component->thisWeek($stream);

    $timestamp = null;
    $datetime = null;
    $firstDayOfWeek = reset($data);

    if (isset($firstDayOfWeek)) {
      $start = $firstDayOfWeek[0]['start'];
      $timestamp = $start['timestamp'];
      $datetime = $start['formatted_date'];
    }

    $scheduled_week = [
      'id' => 'schedule-week',
      'type' => 'week',
      'stream' => $stream,
      'data' => $data,
      'timestamp' => $timestamp,
      'datetime' => $datetime,
    ];

    return $scheduled_week;
  }


  public function getCalendar($stream = EStreams::One) {
    $this->template_name = 'radio_template_schedule';

    $columns = [
      'Time', 'Monday', 'Tuesday', 'Wednesday',
      'Thursday', 'Friday', 'Saturday', 'Sunday',
    ];

    $data = [
      'schedule_calendar_columns' => $columns,
      'scheduled_shows' => $this->getShows($stream),
      'scheduled_day' => $this->getDay($stream),
      'scheduled_week' => $this->getWeek($stream),
      'stream' => $stream,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
