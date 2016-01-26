<?php

class BlogComponent extends BaseComponent {
  public function latest($page = 1) {
    $per_page = 10;
    $start = ($page - 1) * $per_page;

    $query = $this->getLatestQuery();
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    $query = $this->getLatestQuery();
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $events;
    return $pager;
  }


  private function getLatestQuery() {
    $query = new BlogPostQuery();
    $query->getLatest();
    return $query;
  }
}
