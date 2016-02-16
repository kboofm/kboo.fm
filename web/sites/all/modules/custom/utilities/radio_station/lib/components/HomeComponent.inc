<?php

class HomeComponent extends BaseComponent {
  public function latest() {
    $query = new NodeQuery();
    $query->isPromoted();
    $query->propertyOrderBy('sticky', 'DESC');
    $query->addTag('radio_HomeComponent_orderBy');
    $query->setLimit(10);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $items = array_values(
      node_load_multiple($nids)
    );

    return $items;
  }


  public static function orderBy(
    QueryAlterableInterface $query
  ) {

    $query->leftJoin(
      'field_data_field_air_time',
      'field_air_time',
      'node.nid = field_air_time.entity_id'
    );

    $query->leftJoin(
      'publication_date',
      'publication_date',
      'node.nid = publication_date.nid'
    );

    $query->orderBy('field_air_time.field_air_time_value', 'DESC');
    $query->orderBy('publication_date.published_at', 'DESC');
  }
}
