<div class="panel panel-default">
  <div class="panel-body">
    <form id="programs-show-hosts-form"
          action=''
          method='get'>

      <div class="row">
        <div class="col-md-4">
          <div class="form-group">
            <label for="title">
              Host Name
            </label>

            <input type="text"
                   class="form-control"
                   value="<?php print $form['title']; ?>"
                   name="title">
          </div>
        </div>


        <div class="col-md-4">
          <div class="form-group">

            <label for="script-date">
              Status
            </label>

            <select class="form-control"
                    name="status">

              <option value="3" <?php if ($form['status'] == 3):?>selected<?php endif; ?>>
                Any
              </option>

              <option value="1" <?php if ($form['status'] == 1):?>selected<?php endif; ?>>
                Active
              </option>

              <option value="2" <?php if ($form['status'] == 2):?>selected<?php endif; ?>>
                Inactive
              </option>
            </select>
          </div>
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
