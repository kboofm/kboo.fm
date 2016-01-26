<?php

class RadioForms {
  public static function getConfigLivewire($form) {
    $form['radio_station_livewire_lead_in'] = [
      '#type' => 'textarea',
      '#title' => t('Livewire Lead-In'),
      '#default_value' => variable_get('radio_station_livewire_lead_in'),
      '#required' => FALSE,
    ];

    $form['radio_station_livewire_sponsor_info'] = [
      '#type' => 'textarea',
      '#title' => t('Livewire Sponsor Info'),
      '#default_value' => variable_get('radio_station_livewire_sponsor_info'),
      '#required' => FALSE,
    ];

    $form['radio_station_livewire_tomorrow_lead_in'] = [
      '#type' => 'textarea',
      '#title' => t('Livewire Tomorrow Lead-In'),
      '#default_value' => variable_get('radio_station_livewire_tomorrow_lead_in'),
      '#required' => FALSE,
    ];

    $form['radio_station_livewire_lead_out'] = [
      '#type' => 'textarea',
      '#title' => t('Livewire Lead-Out'),
      '#default_value' => variable_get('radio_station_livewire_lead_out'),
      '#required' => FALSE,
    ];

    $form['radio_station_hotline_lead_in'] = [
      '#type' => 'textarea',
      '#title' => t('Hotwire Lead-In'),
      '#default_value' => variable_get('radio_station_hotline_lead_in'),
      '#required' => FALSE,
    ];

    $form['radio_station_hotline_sponsor_info'] = [
      '#type' => 'textarea',
      '#title' => t('Hotwire Sponsor Info'),
      '#default_value' => variable_get('radio_station_hotline_sponsor_info'),
      '#required' => FALSE,
    ];

    $form['radio_station_hotline_tomorrow_lead_in'] = [
      '#type' => 'textarea',
      '#title' => t('Hotwire Tomorrow Lead-In'),
      '#default_value' => variable_get('radio_station_hotline_tomorrow_lead_in'),
      '#required' => FALSE,
    ];

    $form['radio_station_hotline_lead_out'] = [
      '#type' => 'textarea',
      '#title' => t('Hotwire Lead-Out'),
      '#default_value' => variable_get('radio_station_hotline_lead_out'),
      '#required' => FALSE,
    ];

    return system_settings_form($form);
  }
}
