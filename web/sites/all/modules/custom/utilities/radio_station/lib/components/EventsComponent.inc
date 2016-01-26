<?php

class EventsComponent extends BaseComponent {

  public function latest($page = 1) {
    $per_page = 30;
    $start = ($page - 1) * $per_page;

    $query = new EventQuery();
    $query->getLatest();
    $query->count();
    $total_count = $query->execute();

    # Execute for range
    $query = new EventQuery();
    $query->getLatest();
    $query->range($start, $per_page);
    $result = $query->execute();

    $processor = new EventsProcessor();
    $events = $processor->processTable(
      $this->getNids($result)
    );

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count, $per_page);
    $pager['events'] = $events;
    return $pager;
  }


  public function community(
    $count = null,
    $displayStyle = EDisplayStyle::Small
  ) {

    $query = new EventQuery();
    $query->getCommunityEvents();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new EventsProcessor();
    $events = $processor->process(
      $this->getNodes($result),
      $displayStyle
    );

    return $events;
  }


  public function live($count) {
    $query = new EventQuery();
    $query->getLiveEvents();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new EventsProcessor();
    $events = $processor->process(
      $this->getNodes($result),
      EDisplayStyle::Small
    );

    return $events;
  }


  public function upcomingLiveEvents() {
    $query = new EventQuery();
    $query->getLiveEvents();
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    return $events;
  }


  public function previousLiveEvents($page = 1) {
    $per_page = 10;
    $start = ($page - 1) * $per_page;

    $query = $this->getPreviousLiveEventsQuery();
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    $query = $this->getPreviousLiveEventsQuery();
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['events'] = $events;
    return $pager;
  }


  private function getPreviousLiveEventsQuery() {
    $query = new EventQuery();
    $query->getPreviousLiveEvents();
    return $query;
  }


  public function livewire($count) {
    $query = new EventQuery();
    $query->getLivewireEvents();
    $query->setLimit($count);
    $result = $query->execute();

    $processor = new EventsProcessor();
    $events = $processor->process(
      $this->getNodes($result),
      EDisplayStyle::Small
    );

    return $events;
  }


  public function livewireDay($timestamp) {
    $earliest = Helpers::livewireDayBegin($timestamp);
    $latest = Helpers::dayEnd($timestamp);

    $query = new EventQuery();
    $query->getLivewireInRange($earliest, $latest);
    $result = $query->execute();

    $processor = new EventsProcessor();
    return $processor->processLivewireScript(
      $this->getNodes($result)
    );
  }


  public function livewireNextDay($timestamp) {
    $earliest = Helpers::livewireNextDayBegin($timestamp);
    $latest = Helpers::livewireNextDayEnd($timestamp);

    $query = new EventQuery();
    $query->getLivewireInRange($earliest, $latest);
    $result = $query->execute();

    $processor = new EventsProcessor();
    return $processor->processLivewireScript(
      $this->getNodes($result)
    );
  }


  public function livewireVenuesDay($timestamp) {
    $earliest = Helpers::livewireDayBegin($timestamp);
    $latest = Helpers::livewireExtendedDayEnd($timestamp);

    $query = new EventQuery();
    $query->getLivewireInRange($earliest, $latest);
    $result = $query->execute();

    $nids_list = $this->getNodes($result);
    $nids = array_keys($nids_list);
    $processor = new EventsProcessor();

    return $processor->processGeneratedScript(
      $nids
    );
  }


  public function createStubs($stubs) {
    $terms = taxonomy_get_term_by_name(
      'Livewire Music Event',
      'event_types'
    );
    $stub_term = reset($terms);

    foreach ($stubs['event-title'] as $index => $event_title) {
      $node = new stdClass();
      $node->title = check_plain($event_title);
      $node->type = 'event';

      node_object_prepare($node);

      $lang = LANGUAGE_NONE;
      $node->language = $lang;
      $node->uid = 1;
      $node->status = 1;
      $node->active = 1;
      $node->promote = 0;

      // field_event_type
      $node->field_event_type[$lang][] = [
        'tid' => $stub_term->tid
      ];

      // field_event_date
      $event_date = check_plain(
        $stubs['event-date'][$index]
      );

      $event_date = strtotime($event_date);

      if ($event_date === false) {
        continue;
      }

      $node->field_event_date[$lang][] = [
        'value' => $event_date,
      ];

      // field_event_venue
      $event_venue = check_plain(
        $stubs['event-venue'][$index]
      );

      if (!is_numeric($event_venue)) {
        continue;
      }

      $node->field_venue[$lang][] = [
        'target_id' => $event_venue,
      ];

      // field_related_acts
      $event_acts = check_plain(
        $stubs['event-acts'][$index]
      );

      $event_acts = explode(',', $event_acts);
      foreach ($event_acts as $act) {
        if (!is_numeric($act)) {
          continue;
        }

        $node->field_related_acts[$lang][] = [
          'target_id' => $act,
        ];
      }

      node_save($node);
    }
  }
}
