<?php
$column_map = [
  'Playlist Date' => 'PlaylistDate',
  'Show Name' => 'ShowName',
  'On Air Time' => 'OnairTime',
  'Off Air Time' => 'OffairTime',
  'DJ Name' => 'DJName',
];
?>

<table class="table table-striped table-condensed hidden-xs">
  <thead>
    <tr>
      <?php foreach ($column_map as $human => $machine): ?>
        <th>
          <?php print $human; ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </thead>

  <tbody>
  <?php foreach ($spinitron_playlists as $playlist): ?>
    <tr>
      <?php foreach ($column_map as $machine): ?>
        <td>
          <?php print $playlist[$machine]; ?>
        </td>
      <?php endforeach; ?>
    </tr>
  <?php endforeach; ?>
  </tbody>
</table>


<ul class="list-group visible-xs">
  <?php foreach ($spinitron_playlists as $playlist): ?>
    <li class="list-group-item">

      <?php foreach($column_map as $human => $machine): ?>
        <div class="row">

          <div class="col-xs-6">
            <span class="pull-right">
              <?php print $human; ?>
            </span>
          </div>

          <div class="col-xs-6">
            <?php print $playlist[$machine]; ?>
          </div>

        </div>
      <?php endforeach; ?>

    </li>
  <?php endforeach; ?>
</ul>
