<?php

trait MetatagsMigration {
  protected function addMetatagsMapping() {
    $this->addFieldMapping(
      'metatag_description',
      'field_meta_description'
    );

    $this->addFieldMapping(
      'metatag_og:title',
      'field_fb_og_title'
    );

    $this->addFieldMapping(
      'metatag_og:description',
      'field_fb_og_description'
    );

    $this->addImageMapping(
      'metatag_og:image',
      'field_fb_og_image'
    );
  }
}