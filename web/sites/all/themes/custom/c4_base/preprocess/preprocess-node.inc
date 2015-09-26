<?php

function c4_base_alpha_preprocess_node(&$vars) {
  // Provide node template file suggestions for view mode, and
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
  // provide node template file suggestions for node type+view mode.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__' . $vars['view_mode'];
}
