<?php
/**
 * @file
 * configure_theme.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function configure_theme_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function configure_theme_image_default_styles() {
  $styles = array();

  // Exported image style: default_gallery_large_1x.
  $styles['default_gallery_large_1x'] = array(
    'label' => 'default_gallery_large_1x',
    'effects' => array(
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 560,
          'height' => 420,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_gallery_large_2x.
  $styles['default_gallery_large_2x'] = array(
    'label' => 'default_gallery_large_2x',
    'effects' => array(
      13 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1120,
          'height' => 840,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_gallery_large_3x.
  $styles['default_gallery_large_3x'] = array(
    'label' => 'default_gallery_large_3x',
    'effects' => array(
      15 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1680,
          'height' => 1260,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_gallery_large_4x.
  $styles['default_gallery_large_4x'] = array(
    'label' => 'default_gallery_large_4x',
    'effects' => array(
      16 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 2240,
          'height' => 1680,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_gallery_large_5x.
  $styles['default_gallery_large_5x'] = array(
    'label' => 'default_gallery_large_5x',
    'effects' => array(
      17 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 2800,
          'height' => 2100,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_lead_1x.
  $styles['default_lead_1x'] = array(
    'label' => 'default_lead_1x',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 225,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_lead_2x.
  $styles['default_lead_2x'] = array(
    'label' => 'default_lead_2x',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 600,
          'height' => 450,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_lead_3x.
  $styles['default_lead_3x'] = array(
    'label' => 'default_lead_3x',
    'effects' => array(
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 675,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_lead_4x.
  $styles['default_lead_4x'] = array(
    'label' => 'default_lead_4x',
    'effects' => array(
      5 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 900,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_lead_5x.
  $styles['default_lead_5x'] = array(
    'label' => 'default_lead_5x',
    'effects' => array(
      6 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1500,
          'height' => 1125,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_more_1x.
  $styles['default_more_1x'] = array(
    'label' => 'default_more_1x',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 200,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_more_2x.
  $styles['default_more_2x'] = array(
    'label' => 'default_more_2x',
    'effects' => array(
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 400,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_more_3x.
  $styles['default_more_3x'] = array(
    'label' => 'default_more_3x',
    'effects' => array(
      9 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 600,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_more_4x.
  $styles['default_more_4x'] = array(
    'label' => 'default_more_4x',
    'effects' => array(
      10 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 800,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default_more_5x.
  $styles['default_more_5x'] = array(
    'label' => 'default_more_5x',
    'effects' => array(
      11 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
