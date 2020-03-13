<?php

include_once('Response.inc');
class EventsResponse extends Response {

  public function getUpcomingCommunity() {
    $this->template_name = 'radio_template_community_events';

    $component = new EventsComponent();
    $events = $component->community(null, EDisplayStyle::Medium);

    $data = [
      'events' => $events,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getUpcomingLive() {
    $this->template_name = 'radio_template_live_events';

    $component = new EventsComponent();
    $events = $component->upcomingLiveEvents();

    $data = [
      'events' => $events,
    ];
    $this->addTemplateData($data);

    return $this->renderHtml();
  }


  public function getPreviousLive() {
    $this->template_name = 'radio_template_live_events_previous';
    $this->readParams();
    $page = $this->getParam('page', 1);

    $component = new EventsComponent();
    $pager = $component->previousLiveEvents($page);

    $data = [
      'pager' => $pager,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
