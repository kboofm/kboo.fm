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
}
