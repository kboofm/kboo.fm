<?php

class ProgramsPlaylistResponse extends Response {

  public function get() {
    $this->template_name = 'radio_template_programs_playlists';
    return $this->renderHtml();
  }
}
