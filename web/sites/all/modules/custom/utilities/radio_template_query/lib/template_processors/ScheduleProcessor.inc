<?php

class ScheduleProcessor extends TemplateProcessor {

  /**
   * Process programs that come after the given date/time
   *
   * @param $dataset
   * @param $after
   * @param $count
   * @return array
   */
  public function processAfter($dataset, $after, $count = NULL) {
    $schedule = [];

    foreach ($dataset as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $after) {
          continue;
        }

        $schedule_item = $this->buildScheduleItem($wrapped, $timeslot);
        if ($schedule_item) {
          $schedule[] = $schedule_item;
        }
      }
    }

    $this->sortByTimestamp($schedule);

    if ($count) {
      $schedule = array_slice($schedule, 0, $count);
    }

    return $schedule;
  }


  public function processRange($dataset, $start, $end, $groupByDay = false) {
    $schedule = [];

    if ($groupByDay) {
      $schedule = [
        'Sunday' => [],
        'Monday' => [],
        'Tuesday' => [],
        'Wednesday' => [],
        'Thursday' => [],
        'Friday' => [],
        'Saturday' => [],
      ];
    }

    foreach ($dataset as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] < $start) {
          continue;
        }

        if ($timeslot['value'] > $end) {
          continue;
        }

        $schedule_item = $this->buildScheduleItem($wrapped, $timeslot);
        if ($schedule_item) {
          if ($groupByDay) {
            $dayOfWeek = date('l', $timeslot['value']);
            $schedule[$dayOfWeek][] = $schedule_item;
          } else {
            $schedule[] = $schedule_item;
          }
        }
      }
    }

    if ($groupByDay) {
      $this->sortByTimestamp($schedule['Sunday']);
      $this->sortByTimestamp($schedule['Monday']);
      $this->sortByTimestamp($schedule['Tuesday']);
      $this->sortByTimestamp($schedule['Wednesday']);
      $this->sortByTimestamp($schedule['Thursday']);
      $this->sortByTimestamp($schedule['Friday']);
      $this->sortByTimestamp($schedule['Saturday']);
    } else {
      $this->sortByTimestamp($schedule);
    }

    return $schedule;
  }

  private function sortByTimestamp($schedule_items) {
    usort(
      $schedule_items,
      function ($a, $b) {
        return $a['start']['timestamp'] - $b['start']['timestamp'];
      }
    );
  }


  /**
   * Process first item in dataset
   * @param $dataset
   * @return null
   */
  public function processNow($dataset) {
    $now = time();
    reset($dataset);
    $nid = key($dataset);

    $wrapped = entity_metadata_wrapper('node', $nid);
    $timeslots = $wrapped->field_timeslot->value();

    foreach ($timeslots as $timeslot) {
      if ($timeslot['value'] <= $now && $timeslot['value2'] >= $now) {
        return $this->buildScheduleItem($wrapped, $timeslot);
      }
    }

    return NULL;
  }


  private function getTimeslotProgram($wrapped_scheduled_timeslot) {
    try {
      return $wrapped_scheduled_timeslot->field_show->value();
    } catch (EntityMetadataWrapperException $e) {
      return NULL;
    }
  }

  private function getEpisodeProgram($wrapped_episode) {
    $program = NULL;

    if ($wrapped_episode) {
      try {
        $programs = $wrapped_episode->field_produced_for->value();

        if ($programs) {
          $program = $programs[0];
        }
      } catch (EntityMetadataWrapperException $e) {
        // swallow error
      }
    }

    return $program;
  }


  private function getEpisode($timeslot) {
    $query = new StationContentQuery();
    $query->getEpisode(
      $timeslot['value'],
      $timeslot['value2']
    );
    $result = $query->execute();

    if (empty($result)) {
      return NULL;
    }

    reset($result['node']);
    $nid = key($result['node']);
    return entity_metadata_wrapper('node', $nid);
  }


  private function getScheduleUrl($program, $wrapped_episode) {
    if ($wrapped_episode) {
      $episode = $wrapped_episode->value();
      return $this->getEntityUrl($episode);
    }

    return $this->getEntityUrl($program);
  }

  private function getScheduleTitle($timeslot_program, $episode_program) {
    $title = NULL;

    if ($timeslot_program) {
      $title = $timeslot_program->title;
    }

    if ($episode_program && ($episode_program != $timeslot_program)) {
      $title = $episode_program->title;
    }

    return $title;
  }


  private function buildScheduleItem($wrapped_scheduled_timeslot, $timeslot) {
    $wrapped_episode = $this->getEpisode($timeslot);
    $timeslot_program = $this->getTimeslotProgram($wrapped_scheduled_timeslot);
    $episode_program = $this->getEpisodeProgram($wrapped_episode);

    if (!$timeslot_program && !$episode_program) {
      return NULL;
    }

    $title = $this->getScheduleTitle($timeslot_program, $episode_program);
    $url = $this->getScheduleUrl($timeslot_program, $wrapped_episode);

    $schedule_item = [
      'title' => $title,
      'url' => $url,
      'start' => [
        'formatted_date' => date('l M dS, Y', $timeslot['value']),
        'formatted_time' => date('g:i a', $timeslot['value']),
        'timestamp' => $timeslot['value'],
      ],
      'finish' => [
        'formatted_time' => date('g:i a', $timeslot['value2']),
        'timestamp' => $timeslot['value2'],
      ],
    ];

    return $schedule_item;
  }
}
