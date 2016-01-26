<div class="panel panel-default">
  <div class="panel-body">
    <form id="programs-show-hosts-form"
          action=''
          method='get'>

      <div class="row">
        <div class="col-md-4">
          <div class="form-group">
            <label for="street">
              Street
            </label>

            <input type="text"
                   class="form-control"
                   value="<?php print $form['street']; ?>"
                   name="street">
          </div>
        </div>


        <div class="col-md-4">
          <div class="form-group">
            <label for="city">
              City
            </label>

            <input type="text"
                   class="form-control"
                   value="<?php print $form['city']; ?>"
                   name="city">
          </div>
        </div>


        <div class="col-md-4">
          <div class="form-group">
            <label for="zip">
              Zipcode
            </label>

            <input type="text"
                   class="form-control"
                   value="<?php print $form['zip']; ?>"
                   name="zip">
          </div>
        </div>
      </div>

      <div class="row">
        <div class="col-md-4">
          <div class="form-group">
            <label for="title">
              Venue Name
            </label>

            <input type="text"
                   class="form-control"
                   value="<?php print $form['title']; ?>"
                   name="title">
          </div>
        </div>


        <div class="col-md-4">
        </div>


        <div class="col-md-4">
          <button type="submit"
                  id="btn-submit"
                  class="btn btn-default margin-top-md">
            Apply
          </button>
        </div>
      </div>

    </form>
  </div>
</div>
