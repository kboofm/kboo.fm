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
    $programs = [];

    foreach ($dataset as $nid => $item) {
      $entity = entity_metadata_wrapper('node', $nid);
      $timeslots = $entity->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $after) {
          continue;
        }

        $program = $this->getProgram($entity);
        $programs[] = [
          'title' => $program->title,
          'start' => date('Y-m-d H:i:s', $timeslot['value']),
          'timestamp' => $timeslot['value'],
        ];
      }

      usort($programs, function ($a, $b) {
        return $a['timestamp'] - $b['timestamp'];
      });
    }

    $programs = array_slice($programs, 0, $count);
    return $programs;
  }


  /**
   * Process first item in dataset
   * @param $dataset
   * @return null
   */
  public function processFirst($dataset) {
    reset($dataset);
    $nid = key($dataset);
    $entity = entity_metadata_wrapper('node', $nid);
    return $this->getProgram($entity);
  }

  private function getProgram($unwrapped_entity) {
    try {
      return $unwrapped_entity->field_program->value();
    } catch (EntityMetadataWrapperException $e) {
      return NULL;
    }
  }
}
