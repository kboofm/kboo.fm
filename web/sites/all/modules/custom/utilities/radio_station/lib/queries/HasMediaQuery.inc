<?php

class HasMediaQuery extends NodeQuery {
  protected function initialize() {
    $this->addTag('radio_HasMediaQuery_checkHasMedia');
  }

  public function getLatest() {
    $this->hasLeadImage();
    $this->sortByPromotedSticky();
    $this->sortByPublished();

    return $this;
  }

  public static function checkHasMedia(QueryAlterableInterface $query) {
    $query->leftJoin(
      'field_data_field_audio_files',
      'audio_files',
      'node.nid = audio_files.entity_id'
    );

    $query->leftJoin(
      'field_data_field_video_files',
      'video_files',
      'node.nid = video_files.entity_id'
    );

    $query->leftJoin(
      'field_data_field_image_gallery',
      'image_gallery',
      'node.nid = image_gallery.entity_id'
    );

    $query->condition(db_or()
      ->isNotNull('audio_files.field_audio_files_fid')
      ->isNotNull('video_files.field_video_files_fid')
      ->isNotNull('image_gallery.field_image_gallery_target_id')
    );
  }
}
