<?php
if (!isset($playlists)):
  return;
endif;

$song_column_map = [
  'Time' => 'start_time',
  'Artist' => 'artist',
  'Song' => 'song',
  'Album' => 'release',
  'Label' => 'label',
];

$count = count($playlists) - 1;
?>

<div class="margin-vertical-lg">
  <?php foreach ($playlists as $index => $playlist): ?>
    <h4>Episode Playlist</h4>

    <table class="table table-striped table-condensed hidden-xs">
      <thead>
        <tr>
          <?php foreach ($song_column_map as $human => $machine): ?>
            <th>
              <?php print $human; ?>
            </th>
          <?php endforeach; ?>
        </tr>
      </thead>

      <tbody>
      <?php foreach ($playlist['Songs'] as $skey=>$song):
		//first fix the time format
		#$playlists[$index]['Songs'][$skey]['start_time'] = date('g:i', strtotime($song['start']));

		#---no longer necessary after spinitron fix
		//fix for the +/- hours, which strtotime doesn't detect
		#$adjust = substr($song['start'], -5);
		#---no longer necessary after spinitron fix
		$adjust = 0;
		$song['start_time'] = date('g:i', strtotime($song['start'] . ' ' . $adjust . ' hours'));
		$playlist['Songs'][$skey]['start_time'] = date('g:i', strtotime($song['start'] . ' ' . $adjust . ' hours'));
	?>
        <tr>
          <?php foreach ($song_column_map as $machine): ?>
            <td>
              <?php print $song[$machine]; ?>
            </td>
          <?php endforeach; ?>
        </tr>
      <?php endforeach; ?>
      </tbody>
    </table>

    <ul class="list-group visible-xs">
      <?php if(isset($playlist['Songs']) && is_array($playlist['Songs'])):

	foreach ($playlist['Songs'] as $song): ?>
        <li class="list-group-item">

          <?php foreach($song_column_map as $human => $machine): ?>
            <div class="row">

              <div class="col-xs-6">
              <span class="pull-right">
                <?php print $human; ?>
              </span>
              </div>

              <div class="col-xs-6">
                <?php print $song[$machine]; ?>
              </div>

            </div>
          <?php endforeach; ?>

        </li>
      <?php endforeach; endif; ?>
    </ul>


    <?php if ($index < $count): ?>
      <hr class="hidden-xs" />
    <?php endif; ?>
  <?php endforeach; ?>
</div>
