<?php

class StationContentProcessor extends TemplateProcessor {
  public function process($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      $program = "";
      try {
        $programs = $entity->field_produced_for->value();

        if ($programs) {
          $program = $programs[0]->title;
        }
      } catch (EntityMetadataWrapperException $e) {
        // ducktyping
      }

      $unwrapped = $entity->value();
      $nodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'program' => $program,
      ];
    }

    return $nodes;
  }


  public function processUpcoming ($nids) {
    $episodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      try {
        $air_time = $entity->field_air_time->value();
        $starttime = $air_time['value'];
        $endtime = $air_time['value2'];

        $ymd_format = 'Y-m-d';
        $start_day = Helpers::toCarbonString($ymd_format, $starttime);
        $end_day = Helpers::toCarbonString($ymd_format, $endtime);
        $ends_different_day = ($start_day != $end_day);
      } catch (EntityMetadataWrapperException $e) {
        $starttime = "";
        $endtime = "";
        $ends_different_day = false;
      }

      try {
        $summary = $entity->field_short_description->value();
        $summary = check_plain($summary);
      } catch (EntityMetadataWrapperException $e) {
        $summary = "";
      }

      $unwrapped = $entity->value();
      $episodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
        'starttime' => $starttime,
        'endtime' => $endtime,
        'ends_different_day' => $ends_different_day,
        'summary' => $summary,
      ];
    }
    return $episodes;
  }

  public function processUpcomingSlot ($nids) {
    $episodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      try {
        $timeslot = $entity->field_timeslot->value();
	foreach($timeslot as $slot)
	{
		if($slot['value'] < time())
		{
			continue;
		}
		else
		{
			$starttime = $slot['value'];
			$endtime = $slot['value2'];
			break;
		}
	}
        $ymd_format = 'Y-m-d';
        $start_day = Helpers::toCarbonString($ymd_format, $starttime);
        $end_day = Helpers::toCarbonString($ymd_format, $endtime);
        $ends_different_day = ($start_day != $end_day);
      } catch (EntityMetadataWrapperException $e) {
        $starttime = "";
        $endtime = "";
        $ends_different_day = false;
      }

/*
      try {
        $summary = $entity->field_short_description->value();
        $summary = check_plain($summary);
      } catch (EntityMetadataWrapperException $e) {
        $summary = "";
      }
*/

      $unwrapped = $entity->value();
      $episodes[] = [
#        'title' => $this->getTeaserTitle($entity),
        'starttime' => $starttime,
        'endtime' => $endtime,
#        'ends_different_day' => $ends_different_day,
#        'summary' => $summary,
      ];
    }
    return $episodes;
  }

}
