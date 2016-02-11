<?php

class HomeComponent extends BaseComponent {
  public function latest($page = 1) {
    $per_page = 15;
    $start = ($page - 1) * $per_page;

    $query = $this->getQuery();
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    $query = $this->getQuery();
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $events;
    return $pager;
  }


  private function getQuery() {
    $query = new NodeQuery();
    $query->isPromoted();
    $query->addTag('radio_NodeQuery_orderByPublicationDateOrCreated');
    return $query;
  }
}
