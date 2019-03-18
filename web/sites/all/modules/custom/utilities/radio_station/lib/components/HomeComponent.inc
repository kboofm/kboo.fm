<?php

class HomeComponent extends BaseComponent {

  public function latest($lang = 'und') {
    $query = $this->getHomeQuery($lang);
    $result = $query->execute();

    $nids = array_keys(
      $this->getNodes($result)
    );

    $items = array_values(
      node_load_multiple($nids)
    );

    return $items;
  }


  public function latestFeed($lang) {
    $query = $this->getHomeQuery($lang);
    $result = $query->execute();
    return $this->getNids($result);
  }


  private function getHomeQuery($lang) {
    $query = new NodeQuery();
    $query->isPromoted();
    if($lang != 'en' && $lang != 'und')
    {
	$query->setLanguage($lang);
    }
    $query->propertyOrderBy('sticky', 'DESC');
    $query->addTag('radio_HomeComponent_orderBy');
    $query->setLimit(25);
    return $query;
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

    $query->orderBy('field_air_time.field_air_time_value is null');
    $query->orderBy('field_air_time.field_air_time_value', 'ASC');
    $query->orderBy('publication_date.published_at', 'DESC');
  }
}
