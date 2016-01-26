<?php
use Carbon\Carbon;


class LivewireResponse extends Response {
  public function getCalendar() {
    $this->template_name = 'radio_template_livewire_calendar';
    $this->readParams();

    $ymd_format = 'Y-m-d';
    $alt_format = 'l, F j, Y';

    $date = $this->getParam(
      'date',
      Helpers::toCarbonString($ymd_format)
    );

    $timestamp = Helpers::toCarbonTimestamp($ymd_format, $date);
    $heading_date = Helpers::toCarbonString($alt_format, $timestamp);
    $current_date = Helpers::toCarbonString($ymd_format, $timestamp);

    $next_date = Helpers::toCarbonString(
      $ymd_format,
      Helpers::dayAfterBegin($timestamp)
    );

    $prev_date = Helpers::toCarbonString(
      $ymd_format,
      Helpers::dayBeforeBegin($timestamp)
    );

    $component = new EventsComponent();
    $venues = $component->livewireVenuesDay($timestamp);

    $data = [
      'timestamp' => $timestamp,
      'heading_date' => $heading_date,
      'current_date' => $current_date,
      'next_date' => $next_date,
      'prev_date' => $prev_date,
      'venues' => $venues,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }


  public function getGenerator() {
    $this->template_name = 'radio_template_livewire_generator';
    $this->readParams();
    $phase = $this->getParam('phase', ELivewireRoutePhase::EventForm);

    $data = [
      'phase' => $phase,
    ];
    $this->addTemplateData($data);

    switch ($phase) {
      case ELivewireRoutePhase::EventForm:
        $this->getEventForm();
        break;
      case ELivewireRoutePhase::ScriptForm:
        $this->getScriptForm();
        break;
      case ELivewireRoutePhase::GeneratedScript:
        $this->getGeneratedScript();
        break;
    }

    return $this->renderHtml();
  }


  private function getEventForm() {
    $values = [
      'livewire' => [
        'lead_in' => variable_get('radio_station_livewire_lead_in'),
        'lead_out' => variable_get('radio_station_livewire_lead_out'),
        'sponsor_info' => variable_get('radio_station_livewire_sponsor_info'),
        'tomorrow_lead_in' => variable_get('radio_station_livewire_tomorrow_lead_in'),
      ],

      'hotline' => [
        'lead_in' => variable_get('radio_station_hotline_lead_in'),
        'lead_out' => variable_get('radio_station_hotline_lead_out'),
        'sponsor_info' => variable_get('radio_station_hotline_sponsor_info'),
        'tomorrow_lead_in' => variable_get('radio_station_hotline_lead_in'),
      ],
    ];

    $values = json_encode($values);
    $values = htmlentities($values, ENT_QUOTES, 'UTF-8');

    $data = [
      'livewire_hotline_values' => $values,
    ];

    $this->addTemplateData($data);
  }


  private function parseNewlines() {
    $text_newline = "\r\n";
    $html_newline = '<br />';

    $items = [
      'lead-in',
      'sponsor-info',
      'tomorrow-lead-in',
      'lead-out',
    ];

    foreach ($items as $item) {
      $this->params[$item] = str_replace(
        $text_newline,
        $html_newline,
        $this->params[$item]
      );
    }
  }


  private function getScriptForm() {
    $ymd_format = 'Y-m-d';
    $alt_format = 'l, F jS';

    $date = $this->getParam(
      'script-date',
      Helpers::toCarbonString($ymd_format)
    );

    $timestamp = Helpers::toCarbonTimestamp($ymd_format, $date);
    $display_date = Helpers::toCarbonString($alt_format, $timestamp);

    $component = new EventsComponent();
    $day_events = $component->livewireDay($timestamp);
    $next_day_events = $component->livewireNextDay($timestamp);
    $total_count = count($day_events) + count($next_day_events);

    if (count($day_events) == 0) {
      $day_events = null;
    }

    if (count($next_day_events) == 0) {
      $next_day_events = null;
    }

    $this->parseNewlines();

    $lead_params = json_encode($this->params);
    $lead_params = htmlentities($lead_params, ENT_QUOTES, 'UTF-8');

    $data = [
      'display_date' => $display_date,
      'day_events' => $day_events,
      'next_day_events' => $next_day_events,
      'total_count' => $total_count,
      'lead_params' => $lead_params,
    ];

    $this->addTemplateData($data);
  }


  private function getGeneratedScript() {
    $lead_params = (array) json_decode(
      $this->params['lead-params']
    );

    $date = $lead_params['script-date'];
    $alt_format = 'l, F jS';
    $ymd_format = 'Y-m-d';

    $timestamp = Helpers::toCarbonTimestamp($ymd_format, $date);
    $display_date = Helpers::toCarbonString($alt_format, $timestamp);

    $processor = new EventsProcessor();
    $day_venues = $processor->processGeneratedScript(
      $this->params['day-nids'],
      Helpers::livewireDayBegin($timestamp),
      Helpers::dayEnd($timestamp)
    );

    $next_day_venues = $processor->processGeneratedScript(
      $this->params['next-day-nids'],
      Helpers::livewireNextDayBegin($timestamp),
      Helpers::livewireNextDayEnd($timestamp)
    );

    $data = [
      'lead_in' => $lead_params['lead-in'],
      'sponsor_info' => $lead_params['sponsor-info'],
      'tomorrow_lead_in' => $lead_params['tomorrow-lead-in'],
      'lead_out' => $lead_params['lead-out'],
      'day_venues' => $day_venues,
      'next_day_venues' => $next_day_venues,
      'display_date' => $display_date,
    ];

    $this->addTemplateData($data);
  }
}