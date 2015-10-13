<?php

class RadioStation {

  public function createNextEpisodes($count) {
    $schedule = $this->getUpcomingSchedule($count);

    foreach ($schedule as $schedule_item) {
      if ($schedule_item['episode_exists']) {
        continue;
      }

      // create episode
    }
  }


  private function getUpcomingSchedule($count) {
    $now = time();
    $schedule = [];

    $query = new ScheduledTimeslotQuery();
    $query->getNext($count);
    $result = $query->execute();

    foreach ($result['node'] as $nid => $item) {
      $wrapped = entity_metadata_wrapper('node', $nid);
      $timeslots = $wrapped->field_timeslot->value();

      foreach ($timeslots as $timeslot) {
        if ($timeslot['value'] <= $now) {
          continue;
        }

        $schedule[] = $this->buildScheduleItem($timeslot);
      }
    }

    usort($schedule, function ($a, $b) {
      return $a['start'] - $b['start'];
    });

    return array_slice($schedule, 0, $count);
  }

  private function doesEpisodeExist($timeslot) {
    $query = new StationContentQuery();
    $query->getEpisode(
      $timeslot['value'],
      $timeslot['value2']
    );
    $result = $query->execute();
    return !empty($result);
  }

  private function buildScheduleItem($timeslot) {
    $schedule_item = [
      'existing_episode' => $this->doesEpisodeExist($timeslot),
      'start' => $timeslot['value'],
      'finish' => $timeslot['value2'],
    ];

    return $schedule_item;
  }
}