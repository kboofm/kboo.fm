<?php

class VenuesResponse extends Response {
  public function get() {
    $this->template_name = 'radio_template_venues';
    $this->readParams();
    $page = $this->getParam('page', 1);
    $begins = $this->getParam('begins');
    $title = $this->getParam('title');
    $street = $this->getParam('street');
    $city = $this->getParam('city');
    $zip = $this->getParam('zip');

    $search_type = EStringSearchOptions::Contains;
    $search = $title;
    if (!$title && $begins) {
      $search_type = EStringSearchOptions::StartsWith;
      $search = $begins;
    }

    $options = [
      'title' => [
        'value' => $search,
        'search_type' => $search_type,
      ],
      'street' => [
        'value' => $street,
        'search_type' => EStringSearchOptions::Contains,
        'location_type' => ELocationSearchOptions::Street
      ],
      'city' => [
        'value' => $city,
        'search_type' => EStringSearchOptions::Contains,
        'location_type' => ELocationSearchOptions::City
      ],
      'zip' => [
        'value' => $zip,
        'search_type' => EStringSearchOptions::Equals,
        'location_type' => ELocationSearchOptions::Zip
      ],
    ];

    $component = new OrganizationComponent();
    $pager = $component->venues($options, $page);
    $grouped = $component->group($pager['venues']);

    $alpha_pager = RadioPaginator::alphabetic($grouped, $begins, false, false, 'begins');

    $data = [
      'pager' => $pager,
      'alpha_pager' => $alpha_pager,
      'form' => [
        'title' => $title,
        'street' => $street,
        'city' => $city,
        'zip' => $zip,
      ],
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
