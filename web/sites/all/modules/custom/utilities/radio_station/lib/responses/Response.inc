<?php

abstract class Response {
  protected $params;
  protected $template_data;
  protected $template_name;


  public function __construct() {
    $this->template_data = [];
  }


  public function renderHtml() {
    return theme(
      $this->template_name,
      $this->template_data
    );
  }

  public function renderJson() {
    drupal_json_output(
      $this->template_data
    );
  }


  public function renderRss() {
    drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');

    $xml = theme_render_template(
      $this->getTemplateFile(),
      $this->template_data
    );

    print $xml;
    drupal_exit();
  }


  protected function getTemplateFile() {
    $filename = explode('_', $this->template_name);
    array_shift($filename);
    array_shift($filename);
    $filename = join('-', $filename);

    $path = drupal_get_path('module', 'radio_station');
    $filepath = "{$path}/templates/{$filename}.tpl.php";

    return $filepath;
  }


  protected function addTemplateData(array $data) {
    $this->template_data = array_merge(
      $this->template_data,
      $data
    );
  }


  protected function readParams() {
    $this->params = Helpers::getQueryParameters();
  }


  protected function getParam($key, $default = null) {
    return isset($this->params[$key]) ?
      $this->params[$key] : $default;
  }
}
