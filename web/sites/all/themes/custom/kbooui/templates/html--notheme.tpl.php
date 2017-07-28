<?php global $base_url; ?>
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <?php print $head; ?>


  <title>
    <?php print $head_title; ?>
  </title>


  <?php
#     print $styles;
  ?>


  <?php
    $html5shiv = $base_url . '/' . path_to_theme() . '/bower_components/html5shiv/dist/html5shiv.min.js';
  ?>
  <!-- HTML5 element support for IE6-8 -->
  <!--[if lt IE 9]><script src="<?php print $html5shiv; ?>"></script><![endif]-->


  <?php print $scripts; ?>
</head>


<body class="<?php print $classes; ?>" <?php print $attributes; ?>>

  <div class="container-fluid">
    <?php print $page_top; ?>
  </div>

  <div class="container main-body">
    <?php print $page; ?>
  </div>

  <?php print $page_bottom; ?>
</body>


</html>
