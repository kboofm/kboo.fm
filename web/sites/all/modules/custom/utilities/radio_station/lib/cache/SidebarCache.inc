<?php

class SidebarCache extends BaseCache {

  public function __construct() {
    parent::__construct();
    $this->keyPrefix = "radio_station_latest_";
  }


  public function clear($node) {
    if ($node->type != "station_content") {
      return;
    }

    $this->clearPlaylists();
    $this->clearAudio($node);
  }


  public function clearPlaylists() {
    $this->forceClear("playlists");
  }


  public function clearAudio($node) {
    $clear = false;
    $entity = entity_metadata_wrapper('node', $node);

    try {
      $audio_files = $entity->field_audio_files->value();
      if (count($audio_files) > 0) {
        $clear = true;
      }
    } catch (EntityMetadataWrapperException $e) {
      // duck typing
    }

    if ($clear) {
      $this->forceClear("audio");
    }
  }
}
