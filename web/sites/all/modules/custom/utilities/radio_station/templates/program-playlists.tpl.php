<form id="form-programs-playlists"
      action=''
      method='get'>

  <div class="row">
    <div class="col-md-3 col-md-offset-1">
      <div class="form-group">
        <input type="text"
               class="form-control"
               id="id-artist"
               placeholder="Artist">
      </div>
    </div>


    <div class="col-md-3 col-md-offset-1">
      <div class="form-group">
        <input type="text"
               class="form-control"
               id="id-title"
               placeholder="Title">
      </div>
    </div>


    <div class="col-md-3 col-md-offset-1">
      <div class="form-group">
        <input type="text"
               class="form-control"
               id="id-album"
               placeholder="Album">
      </div>
    </div>
  </div>


  <div class="row">
    <div class="col-md-3 col-md-offset-1">
      <div class="form-group">
        <input type="text"
               class="form-control"
               id="id-date-from"
               placeholder="Date From"
               data-provide="datepicker">
      </div>
    </div>

    <div class="col-md-3 col-md-offset-1">
      <div class="form-group">
        <input type="text"
               class="form-control"
               id="id-date-to"
               placeholder="Date To"
               data-provide="datepicker">
      </div>
    </div>

    <div class="col-md-3 col-md-offset-1">

      <button type="button"
              id="btn-submit"
              class="btn btn-default">
        Apply
      </button>
    </div>
  </div>

</form>


<hr />


<div class="row margin-top-lg">
  <div class="col-md-10 col-md-offset-1 playlists">

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


