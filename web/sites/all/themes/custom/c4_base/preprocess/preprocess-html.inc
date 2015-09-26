<?php


function c4_base_alpha_preprocess_html(&$vars) {

  // path_to_theme() returns omega here not our subtheme
  $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
  $full_theme_path = $GLOBALS['base_url'] . base_path() . $theme_path;

  // ensure IE9 does not show compatibility mode
  $meta_ie_render_engine = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'X-UA-Compatible',
        'content' =>  'IE=edge,chrome=1',      
        ),
      '#weight' => '-99999',
      );
  drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');

  /* conditional IE9 stylesheet for things such as filter:none and so forth */
  drupal_add_css( $theme_path . '/css/alpha-default-gte-ie9.css', array(
        'type' => 'file',
        'group' => 2000,
        'media' => 'all',
        'browsers' => array('IE' => '(gte IE 9)&(!IEMobile)', '!IE' => FALSE),
        'weight' => 100
        ));

  // css3 selectors for ie8, thanks to http://selectivizr.com/
  // sigh, no browser conditional support for add_js yet http://drupal.org/node/865536
  // so using drupal_html_head instead, though it does output this before the title tag which is rather fugly.
  $ie8_conditional_js = '<!--[if (gte IE 6)&(lte IE 8)]><script type="text/javascript" src="' . $full_theme_path.'/js/selectivizr-min.js' . '"></script><![endif]-->'."\n";
  $ie8_conditional_js = array(
      '#type' => 'markup',
      '#markup' => $ie8_conditional_js,
      '#weight' => 99999
      );
  drupal_add_html_head($ie8_conditional_js, 'ie8_conditional_js');  

  // favicons - presumes favicon.ico in base of theme directory, and a favicons directory with all variants in it

  drupal_add_html_head_link(array('rel' => 'shortcut icon', 'href' => $full_theme_path  . '/favicon.ico'));
   
  // non-retina iPhone pre iOS 7 
  drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path  . '/favicons/touch-icon-iphone.png', 'sizes' => '57x57'));

  // non-retina iPad pre iOS 7
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/icon76.png', 'sizes' => '72x72'));

  // non-retina iPad iOS 7  
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/touch-icon-ipad.png', 'sizes' => '76x76'));  
    
  // retina iPhone pre iOS 7  
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/touch-icon-iphone4.png', 'sizes' => '114x114'));
    
  // retina iPhone iOS 7 
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/icon120.png', 'sizes' => '120x120')); 
    
  // retina iPad pre iOS 7
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/icon144.png', 'sizes' => '144x144')); 
    
  // retina iPad iOS 7 
    drupal_add_html_head_link(array('rel' => 'apple-touch-icon', 'href' => $full_theme_path . '/favicons/icon152.png', 'sizes' => '152x152'));     

  // IE11 Tiles
  $ms70 = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-square70x70logo', 
      'content' => $full_theme_path . '/favicons/tile-tiny.png',
    ),
  );
  drupal_add_html_head($ms70, 'msapplication-square70x70logo');
  
  $ms150 = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-square150x150logo', 
      'content' => $full_theme_path . '/favicons/tile-square.png',
    ),
  );
  drupal_add_html_head($ms150, 'msapplication-square150x150logo');
  
  $ms310w = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-wide310x150logo', 
      'content' => $full_theme_path . '/favicons/tile-wide.png',
    ),
  );
  drupal_add_html_head($ms310w, 'msapplication-wide310x150logo');
  
  $ms310 = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-square310x310logo', 
      'content' => $full_theme_path . '/favicons/tile-large.png',
    ),
  );
  drupal_add_html_head($ms310, 'msapplication-square310x310logo');

  // Win8 tile
  $tileimage = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-TileImage', 
      'content' => $full_theme_path . '/favicons/favicon-144.png',
    ),
  );
  drupal_add_html_head($tileimage, 'msapplication-TileImage');
  
  $tilecolor = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'msapplication-TileColor', 
      'content' => '#ffffff',
    ),
  );
  drupal_add_html_head($tilecolor, 'msapplication-TileColor');
  
  $appname = array(
    '#tag' => 'meta', 
    '#attributes' => array( 
      'name' => 'application-name', 
      'content' => 'DP Global Solutions',
    ),
  );
  drupal_add_html_head($appname, 'application-name');

}
