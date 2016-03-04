<?php

abstract class Response {
  protected $params;
  protected $template_data;
  protected $template_name;


  public function __construct() {
    $this->template_data = [];
  }


  protected static function getEntityFromAlias($program_alias, $type) {
    $pattern = variable_get("pathauto_node_{$type}_pattern", $type);
    $pattern = explode("/", $pattern);
    $pattern = reset($pattern);
    $url_alias = "{$pattern}/{$program_alias}";

    $path = drupal_lookup_path("source", $url_alias);
    if (!$path) {
      return null;
    }

    $node = menu_get_object("node", 1, $path);
    if (!$node) {
      return null;
    }

    if ($node->type != $type) {
      return null;
    }

    return entity_metadata_wrapper('node', $node);
  }


  public static function getTitleFromAlias($program_alias, $type) {
    $title = "";
    $entity = Response::getEntityFromAlias(
      $program_alias,
      $type
    );

    if ($entity) {
      $title = $entity->title->value();
    }

    return $title;
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
    drupal_add_http_header(
      'Content-Type',
      'application/rss+xml; charset=utf-8'
    );

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
