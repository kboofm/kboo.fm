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

  private function getProgram($wrapped) {
    try {
      return $wrapped->field_program->value();
    } catch (EntityMetadataWrapperException $e) {
      return NULL;
    }
  }

  private function buildScheduleItem($wrapped, $timeslot) {
//    $episode = $this->getEpisode($timeslot);
//    $program = $this->getProgram($wrapped, $episode);
    $program = $this->getProgram($wrapped);
    $program_url = $this->getEntityUrl($program);

    $schedule_item = [
      'program' => [
        'title' => $program->title,
        'url' => $program_url,
      ],
      'start' => date('Y-m-d H:i:s', $timeslot['value']),
      'timestamp' => $timeslot['value'],
    ];

    return $schedule_item;
  }
}
