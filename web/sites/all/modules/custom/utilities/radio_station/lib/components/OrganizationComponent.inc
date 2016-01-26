<?php

class OrganizationComponent extends BaseComponent {

  public function getSelect2($startswith) {
    $query = new OrganizationQuery();
    $query->getVenues();
    $query->searchTitle($startswith, EStringSearchOptions::StartsWith);
    $query->setLimit(10);
    $result = $query->execute();

    $processor = new ListProcessor();
    $list = $processor->processSelect2(
      $this->getNids($result)
    );

    return [
      'results' => $list,
      'more' => false
    ];
  }


  public function venues($options, $page = 1) {
    $per_page = 50;
    $start = ($page - 1) * $per_page;

    $query = $this->getVenueQuery($options);
    $query->count();
    $total_count = $query->execute();

    # Execute for range
    $query = $this->getVenueQuery($options);
    $query->range($start, $per_page);
    $result = $query->execute();

    $processor = new ListProcessor();
    $venues = $processor->process(
      $this->getNids($result)
    );

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count, $per_page);
    $pager['venues'] = $venues;
    return $pager;
  }


  private function getVenueQuery($options) {
    $query = new OrganizationQuery();
    $query->getVenues();

    if (isset($options['title'])) {
      $query->searchTitle(
        $options['title']['value'],
        $options['title']['search_type']
      );
    }

    $locations = [
      'street',
      'city',
      'zip',
    ];

    array_walk(
      $locations,
      function ($item) use ($query, $options) {
        if (!empty($options[$item]['value'])) {
          $query->locationSearch(
            $options[$item]['value'],
            $options[$item]['search_type'],
            $options[$item]['location_type']
          );
        }
      }
    );

    return $query;
  }
}
