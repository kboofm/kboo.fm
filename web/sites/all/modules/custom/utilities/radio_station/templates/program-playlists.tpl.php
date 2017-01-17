<div class="row margin-top">
  <div class="col-xs-12 playlists">


<?php
//pre-grab playlist to know number of titles and their keys
$r = new RadioSpinitron();
$progs = $r->getLatestSongsTitles();
foreach($progs as $key=>$prog):
?>
    <table class="table table-striped table-condensed table-<?php print $key; ?>">
      <caption data-bind="prog-<?php print $key; ?>"></caption>
      <thead>
        <tr>
          <th data-bind="col"></th>
        </tr>
      </thead>

      <tbody>
        <tr>
          <td data-bind="artist-<?php print $key; ?>"></td>
          <td data-bind="title-<?php print $key; ?>"></td>
          <td data-bind="album-<?php print $key; ?>"></td>
          <td data-bind="date-<?php print $key; ?>"></td>
          <td data-bind="time-<?php print $key; ?>"></td>
        </tr>
      </tbody>
    </table>
<?php
endforeach;
?>


    <div class="text-center margin-bottom-lg"
         data-bind="throbber">
        Loading, please wait...
    </div>

  </div>
</div>


