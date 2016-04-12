<?php

class RadioForms {

  public static function getStreams($form) {
    $form['radio_station_stream_one_nid'] = [
      '#type' => 'textfield',
      '#title' => "Stream 1 - node nid",
      '#default_value' => variable_get('radio_station_stream_one_nid'),
      '#required' => FALSE,
    ];

    $form['radio_station_stream_two_nid'] = [
      '#type' => 'textfield',
      '#title' => "Stream 2 - node nid",
      '#default_value' => variable_get('radio_station_stream_two_nid'),
      '#required' => FALSE,
    ];

    return system_settings_form($form);
  }
}
