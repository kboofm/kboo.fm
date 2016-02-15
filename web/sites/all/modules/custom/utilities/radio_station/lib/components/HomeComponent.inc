<?php

class HomeComponent extends BaseComponent {
  public function latest($page = 1) {
    $per_page = 15;
    $start = ($page - 1) * $per_page;

    $query = new NodeQuery();
    $query->isPromoted();
    $query->addTag('radio_HomeComponent_orderByAirDateOrPublicationDate');
    $query->range($start, $per_page);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $events = array_values(
      node_load_multiple($nids)
    );

    $query = new NodeQuery();
    $query->isPromoted();
    $query->count();
    $total_count = $query->execute();

    $paginator = new RadioPaginator();
    $pager = $paginator->paginate($page, $total_count);
    $pager['items'] = $events;
    return $pager;
  }


  public static function orderByAirDateOrPublicationDate(
    QueryAlterableInterface $query
  ) {

    $query->leftJoin(
      'field_data_field_air_time',
      'field_data_field_air_time',
      'node.nid = field_data_field_air_time.entity_id'
    );

    $query->leftJoin(
      'publication_date',
      'publication_date',
      'node.nid = publication_date.nid'
    );

    $query->orderBy('ifnull(field_data_field_air_time.field_air_time_value, publication_date.published_at)', 'DESC');
  }
}
