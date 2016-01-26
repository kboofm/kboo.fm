<form id="livewire-events-form"
      class="margin-top-lg"
      action=''
      method='get'>

  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Script Date
      </h3>
    </div>

    <div class="panel-body">
      <div class="row">
        <div class="col-md-4">
          <div class="form-group">
            <label for="script-date">
              Date to generate the script
            </label>

            <input type="text"
                   class="form-control"
                   name="script-date">
          </div>
        </div>
      </div>
    </div>
  </div>


  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Script Type
      </h3>
    </div>

    <div class="panel-body">
      <div class="row">
        <div class="col-md-4">
          <div class="form-group">

            <label for="script-date">
              Select the type of script to generate
            </label>

            <select class="form-control"
                    name="script-type">

              <option value="livewire">
                Livewire
              </option>

              <option value="hotline">
                Hotline
              </option>
            </select>
          </div>
        </div>
      </div>
    </div>
  </div>


  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Lead-In Text
      </h3>
    </div>

    <div class="panel-body">
      <div class="form-group">
        <textarea class="form-control"
                  rows="5"
                  data-bind="lead-in"
                  name="lead-in"></textarea>
      </div>
    </div>
  </div>


  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Sponsor Information
      </h3>
    </div>

    <div class="panel-body">
      <div class="form-group">
        <textarea class="form-control"
                  rows="5"
                  data-bind="sponsor-info"
                  name="sponsor-info"></textarea>
      </div>
    </div>
  </div>


  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Tomorrow's Lead-In Text
      </h3>
    </div>

    <div class="panel-body">
      <div class="form-group">
        <textarea class="form-control"
                  rows="5"
                  data-bind="tomorrow-lead-in"
                  name="tomorrow-lead-in"></textarea>
      </div>
    </div>
  </div>


  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title">
        Lead-Out Text
      </h3>
    </div>

    <div class="panel-body">
      <div class="form-group">
        <textarea class="form-control"
                  rows="5"
                  data-bind="lead-out"
                  name="lead-out"></textarea>
      </div>
    </div>
  </div>


  <div class="row margin-vertical-lg">
    <div class="col-md-4 col-md-offset-4">
      <button type="submit"
              id="btn-submit"
              class="btn btn-default">
        Display Events
      </button>
    </div>
  </div>


  <input type="hidden"
         name="phase"
         value="<?php print ELivewireRoutePhase::ScriptForm; ?>">


  <input type="hidden"
         name="livewire-hotline-values"
         data-values="<?php print $livewire_hotline_values; ?>">
</form>
