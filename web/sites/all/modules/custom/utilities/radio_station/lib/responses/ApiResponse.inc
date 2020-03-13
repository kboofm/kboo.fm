<?php

include_once('Response.inc');
class ApiResponse extends Response {

  public function getEpisode($stream, $direction, $timestamp) {
    $component = new ScheduleComponent();
    $data = $component->getShow($stream, $direction, $timestamp);
    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getDay($stream, $direction, $timestamp) {
    $component = new ScheduleComponent();
    $data = $component->getDay($stream, $direction, $timestamp);
    $this->addTemplateData($data);
    $this->renderJson();
  }


  public function getWeek($stream, $direction, $timestamp) {
    $component = new ScheduleComponent();
    $data = $component->getWeek($stream, $direction, $timestamp);
    $this->addTemplateData($data);
    $this->renderJson();
  }
}
