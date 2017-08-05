<?php
#test for #nested_audio
$af = array();
if(isset($variables['element']['#nested_audio']) && $variables['element']['#nested_audio'] && $variables['element']['#field_name'] == 'field_audio_files')
{
	$af['audio_files_source'] = $variables['element']['#object'];
	print theme('radio_template_audio_player', $af);
}
else if($variables['element']['#view_mode'] == 'rss' && isset($variables['element']['#object']->field_audio_files['und'][0]['uri']))
{
	$file = $variables['element']['#object']->field_audio_files['und'][0];
	$url = file_create_url($file['uri']);
	$filesize = $file['filesize'];
#	print '<enclosure url="' . $url . '" length="' . $filesize . '" type="audio/mpeg" />';
	print '<div class="enclosures">Media files';
	print '<div class="enclosure">';
	print '<a href="' . $url . '" >';
	print $file['filename'];
	print '</a> (audio/mpeg, ' . round($filesize/(1024*1024),1) . ' MB)';
	print '</div></div>';
}
?>
