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
  public function processAfter($dataset, $after, $count) {
    $schedule = [];

    foreach ($dataset as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $after) {
          continue;
        }

        $schedule[] = $this->buildScheduleItem($wrapped, $timeslot);
      }

      usort($schedule, function ($a, $b) {
        return $a['timestamp'] - $b['timestamp'];
      });
    }

    $schedule = array_slice($schedule, 0, $count);
    return $schedule;
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

  private function getProgram($wrapped, $wrapped_episode) {
    $program = NULL;

    if ($wrapped_episode) {
      try {
        $programs = $wrapped_episode->field_produced_for->value();
        $program = $programs[0];
      } catch (EntityMetadataWrapperException $e) {
        // swallow error
      }
    }

    if (!$program) {
      try {
        $program = $wrapped->field_program->value();
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

  private function buildScheduleItem($wrapped, $timeslot) {
    $wrapped_episode = $this->getEpisode($timeslot);
    $program = $this->getProgram($wrapped, $wrapped_episode);

    $title = $program->title;
    $url = $this->getEntityUrl($program);
    if ($wrapped_episode) {
      $episode = $wrapped_episode->value();
      $url = $this->getEntityUrl($episode);
    }

    $schedule_item = [
      'title' => $title,
      'url' => $url,
      'start' => date('Y-m-d H:i:s', $timeslot['value']),
      'timestamp' => $timeslot['value'],
    ];

    return $schedule_item;
  }
}
