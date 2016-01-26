<?php

class StationContentComponent extends BaseComponent {
  public function getContentForProgram($program_nid, $page = 1) {
    $per_page = 10;
    $start = ($page - 1) * $per_page;

    $query = new StationContentQuery();
    $query = $query->getContentByProgram($program_nid);
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $episodes = array_values(
      node_load_multiple($nids)
    );

    $query = new StationContentQuery();
    $query = $query->getContentByProgram($program_nid);
    $query->range($start, $per_page);
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $episodes;
    return $pager;
  }
}
