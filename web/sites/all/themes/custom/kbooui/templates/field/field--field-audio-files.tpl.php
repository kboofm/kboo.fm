<?php
#test for #nested_audio
$af = array();
if(isset($variables['element']['#nested_audio']) && $variables['element']['#nested_audio'] && $variables['element']['#field_name'] == 'field_audio_files')
{
	$af['audio_files_source'] = $variables['element']['#object'];
}
?>
<?php print theme('radio_template_audio_player', $af);
