<div class="row margin-top">
  <div class="col-xs-12 playlists">

    <table class="table table-striped table-condensed">
      <thead>
        <tr>
          <th data-bind="col"></th>
        </tr>
      </thead>

      <tbody>
        <tr>
          <td data-bind="artist"></td>
          <td data-bind="title"></td>
          <td data-bind="album"></td>
          <td data-bind="date"></td>
          <td data-bind="time"></td>
        </tr>
      </tbody>
    </table>


    <div class="text-center margin-bottom-lg"
         data-bind="throbber">
        Loading, please wait...
    </div>

  </div>
</div>


