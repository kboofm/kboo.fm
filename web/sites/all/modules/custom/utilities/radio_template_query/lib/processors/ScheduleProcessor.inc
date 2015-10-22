<?php

class ScheduleProcessor extends TemplateProcessor {

  public function process($dataset, $timestamp, $when, $count = 1) {
    $schedule = [];

    foreach ($dataset as $nid => $item) {
      $wrapped_node = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped_node->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($when == 'after' && $timeslot['value'] <= $timestamp) {
          continue;
        } else if ($when == 'before' && $timeslot['value'] >= $timestamp) {
          continue;
        }

        $schedule_item = $this->buildScheduleItem($wrapped_node, $timeslot);
        if ($schedule_item) {
          $schedule[] = $schedule_item;
        }
      }
    }

    $direction = ($when == 'after') ? 'ASC' : 'DESC';
    $this->sortByStartTime($schedule, $direction);

    if ($count) {
      $schedule = array_slice($schedule, 0, $count);
    }

    return $schedule;
  }


  public function processRange($dataset, $start, $end, $groupByDay = false) {
    $schedule = [];

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

            if (!isset($schedule[$dayOfWeek])) {
              $schedule[$dayOfWeek] = [];
            }

            $schedule[$dayOfWeek][] = $schedule_item;
          } else {
            $schedule[] = $schedule_item;
          }
        }
      }
    }

    if ($groupByDay) {
      foreach ($schedule as &$dayOfWeek) {
        $this->sortByStartTime($dayOfWeek);
      }
    } else {
      $this->sortByStartTime($schedule);
    }

    return $schedule;
  }

  private function sortByStartTime(&$schedule_items, $direction = 'ASC') {
    usort(
      $schedule_items,
      function ($a, $b) use ($direction) {
        $left = $a['start']['timestamp'];
        $right = $b['start']['timestamp'];

        if ($direction == 'ASC') {
          return ($left < $right) ? -1 : 1;
        } else {
          return ($left > $right) ? -1 : 1;
        }
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


  private function getShowHost($timeslot_program, $episode_program) {
    $showhost_id = NULL;

    if ($timeslot_program && isset($timeslot_program->field_hosted_by['und'][0]['target_id'])) {
      $showhost_id = $timeslot_program->field_hosted_by['und'][0]['target_id'];
    }

    if ($episode_program && ($episode_program != $timeslot_program)) {
      if (isset($episode_program->field_hosted_by['und'][0]['target_id'])) {
        $showhost_id = $episode_program->field_hosted_by['und'][0]['target_id'];
      }
    }

    if (!$showhost_id) {
      return NULL;
    }

    $showhost = entity_metadata_wrapper('node', $showhost_id);
    return $showhost->value();
  }


  private function buildScheduleItem($wrapped_scheduled_timeslot, $timeslot) {
    $wrapped_episode = $this->getEpisode($timeslot);
    $timeslot_program = $this->getTimeslotProgram($wrapped_scheduled_timeslot);
    $episode_program = $this->getEpisodeProgram($wrapped_episode);

    if (!$timeslot_program && !$episode_program) {
      return NULL;
    }

    $title = $this->getScheduleTitle($timeslot_program, $episode_program);
    $showhost = $this->getShowHost($timeslot_program, $episode_program);
    $url = $this->getScheduleUrl($timeslot_program, $wrapped_episode);

    $showhost_title = NULL;
    $showhost_url = NULL;
    if ($showhost) {
      $showhost_title = $showhost->title;
      $showhost_url = $this->getEntityUrl($showhost);
    }

    $schedule_item = [
      'title' => $title,
      'url' => $url,
      'showhost' => [
        'name' => $showhost_title,
        'url' => $showhost_url,
      ],
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
