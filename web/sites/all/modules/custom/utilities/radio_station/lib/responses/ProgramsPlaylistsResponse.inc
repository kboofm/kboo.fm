<?php

include_once('Response.inc');
class ProgramsPlaylistResponse extends Response {

  public function get() {
    $this->template_name = 'radio_template_program_playlists';
    return $this->renderHtml();
  }
}
