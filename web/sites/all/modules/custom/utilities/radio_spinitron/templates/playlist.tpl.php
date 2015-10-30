<table class="table table-striped table-condensed">
  <thead>
  <tr>
    <th>Playlist Date</th>
    <th>Show Name</th>
    <th>On Air Time</th>
    <th>Off Air Time</th>
    <th>DJ Name</th>
  </tr>
  </thead>
  <tbody>
  <?php foreach ($spinitron_playlists as $playlist): ?>
        <tr>
          <td>
            <?php print $playlist['PlaylistDate']; ?>
          </td>

          <td>
            <?php print $playlist['ShowName']; ?>
          </td>

          <td>
            <?php print $playlist['OnairTime']; ?>
          </td>

          <td>
            <?php print $playlist['OffairTime']; ?>
          </td>

          <td>
            <?php print $playlist['DJName']; ?>
          </td>
        </tr>
  <?php endforeach; ?>
  </tbody>
</table>
