<?php

class ScheduleComponent extends BaseComponent {

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


  public function getShow($stream, $direction, $timestamp) {
    $weekData = $this->getWeek($stream, "at", $timestamp);
    $dayOfWeek = Helpers::dayOfWeek($timestamp);
    $dayData = $weekData[$dayOfWeek];

    $shows = array_filter(
      $dayData,
      function ($show) use ($timestamp) {
        $segment_start = $show['start']['timestamp'];
        $segment_end = $show['finish']['timestamp'];

        $begun = ($timestamp >= $segment_start);
        $ended = ($timestamp >= $segment_end);

        return ($begun && !$ended);
      }
    );

    $indexes = array_keys($shows);
    $index = array_pop($indexes);

    switch ($direction) {
      case 'at':
        return $shows;

      case 'prev':
        $index -= 1;

        if ($index < 0) {
          $dayOfWeek = $this->getDayOfWeek($dayOfWeek, $direction);

          if ($dayOfWeek == 'saturday') {
            $weekData = $this->getWeek($stream, $direction, $timestamp);
          }

          $index = count($weekData[$dayOfWeek]) - 1;
        }

        $dayData = $weekData[$dayOfWeek];
        $shows = $dayData[$index];
        return [$shows];

      case 'next':
        $index += 1;

        if ($index >= count($dayData)) {
          $index = 0;
          $dayOfWeek = $this->getDayOfWeek($dayOfWeek, $direction);

          if ($dayOfWeek == 'sunday') {
            $weekData = $this->getWeek($stream, $direction, $timestamp);
          }
        }

        $dayData = $weekData[$dayOfWeek];
        $shows = $dayData[$index];
        return [$shows];

      default:
        return [];
    }
  }


  private function getDayOfWeek($dayOfWeek, $direction) {
    switch ($dayOfWeek) {
      case 'sunday':
        return ($direction == 'next') ? 'monday' : 'saturday';
      case 'monday':
        return ($direction == 'next') ? 'tuesday' : 'sunday';
      case 'tuesday':
        return ($direction == 'next') ? 'wednesday' : 'monday';
      case 'wednesday':
        return ($direction == 'next') ? 'thursday' : 'tuesday';
      case 'thursday':
        return ($direction == 'next') ? 'friday' : 'wednesday';
      case 'friday':
        return ($direction == 'next') ? 'saturday' : 'thursday';
      case 'saturday':
        return ($direction == 'next') ? 'sunday' : 'friday';
      default:
        return 'sunday';
    }
  }


  public function getDay($stream, $direction, $timestamp) {
    $data = [];

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
        return $data;
    }

    $weekBegin = $this->getWeekBegin($start);
    $data = $this->getWeek($stream, "at", $weekBegin);
    $dayOfWeek = Helpers::dayOfWeek($start);
    return $data[$dayOfWeek];
  }


  public function getWeek($stream, $direction, $timestamp) {
    $weekBegin = $this->getWeekBegin($timestamp, $direction);

    if (!$weekBegin) {
      return [];
    }

    $cache_key = "radio_station_week_{$stream}_{$weekBegin}";
    $cache_table = "cache_radio_station_schedule";

    if ($cache = cache_get($cache_key, $cache_table)) {
      $data = $cache->data;
    } else {
      $data = $this->loadWeek($stream, $direction, $timestamp);
      cache_set($cache_key, $data, $cache_table);
    }

    return $data;
  }


  private function getWeekBegin($timestamp, $direction = "at") {
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

    return $start;
  }


  private function loadWeek($stream, $direction, $timestamp) {
    $data = [];
    $start = $this->getWeekBegin($timestamp, $direction);

    if (!$start) {
      return $data;
    }

    $end = Helpers::weekEnd($start);
    $query = new ScheduledTimeslotQuery();
    $query->getRange($stream, $start, $end);
    $result = $query->execute();

    if (empty($result)) {
      return $data;
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
