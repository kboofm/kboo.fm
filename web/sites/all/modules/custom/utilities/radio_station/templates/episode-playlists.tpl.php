<?php
if (!isset($playlists)):
  return;
endif;

$song_column_map = [
  'Time' => 'Timestamp',
  'Artist' => 'ArtistName',
  'Song' => 'SongName',
  'Album' => 'DiskName',
  'Label' => 'LabelName',
];

$count = count($playlists) - 1;
?>

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
    <?php foreach ($playlist['Songs'] as $song): ?>
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
    <?php foreach ($playlist['Songs'] as $song): ?>
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
    <?php endforeach; ?>
  </ul>


  <?php if ($index < $count): ?>
    <hr class="hidden-xs" />
  <?php endif; ?>
<?php endforeach; ?>
