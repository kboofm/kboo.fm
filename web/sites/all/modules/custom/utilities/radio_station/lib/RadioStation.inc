<?php

class RadioStation {
  public function createNextEpisodes($count) {
    $query = new ScheduledTimeslotQuery();
    $query->getNext($count);
    $result = $query->execute();

    $dataset = $result['node'];
    $after = time();

    foreach ($dataset as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $after) {
          continue;
        }

//        $schedule[] = $this->buildScheduleItem($wrapped, $timeslot);
      }

//      usort($schedule, function ($a, $b) {
//        return $a['timestamp'] - $b['timestamp'];
//      });
    }
  }
}