<form id="events-quickadd-form"
      class="margin-top-lg"
      action=""
      method="post">

  <div class="panel panel-default">
    <div class="panel-heading">
      <div class="row">

        <div class="col-sm-6">
          <h3 class="panel-title">
            Event
          </h3>
        </div>


        <div class="col-sm-6 form-inline">
          <div class="pull-right">

            <div class="form-group input-group">
              <input type="text"
                     class="form-control"
                     name="event-count[]"
                     value="1">


              <span class="input-group-btn">
                <button type="button"
                        class="btn btn-info event-copy"
                        title="Copy">

                  <i class="fa fa-copy"></i>
                </button>
              </span>
            </div>


            <button type="button"
                    class="form-group btn btn-info event-new"
                    title="New">

              <i class="fa fa-file-o"></i>
            </button>


            <button type="button"
                    class="form-group btn btn-info event-trash"
                    title="Trash">

              <i class="fa fa-trash-o"></i>
            </button>

          </div>
        </div>
      </div>
    </div>


    <div class="panel-body">
      <div class="row">
        <div class="col-sm-6">
          <div class="form-group">
            <input type="text"
                   class="form-control"
                   name="event-title[]"
                   placeholder="Title">

            <div class="validation-response">
              <span data-bind="message"></span>
            </div>
          </div>
        </div>


        <div class="col-sm-6">
          <div class="form-group">
            <div class="input-group">
              <input type="text"
                     class="form-control"
                     name="event-date[]"
                     placeholder="Date/Time">

              <span class="input-group-addon">
                <i class="fa fa-calendar"></i>
              </span>
            </div>

            <div class="validation-response">
              <span data-bind="message"></span>
            </div>
          </div>
        </div>
      </div>


      <div class="row">
        <div class="col-sm-6">
          <div class="form-group">
            <input name="event-venue[]"
                   type="hidden"/>

            <div class="validation-response">
              <span data-bind="message"></span>
            </div>
          </div>
        </div>


        <div class="col-sm-6">
          <div class="form-group">
            <input name="event-acts[]"
                   type="hidden"/>
          </div>
        </div>
      </div>
    </div>
  </div>


  <div class="row margin-vertical-lg">
    <div class="col-sm-4 col-sm-offset-4 text-center">
      <button type="submit"
              id="btn-submit"
              class="btn btn-default">
        Create Events
      </button>
    </div>
  </div>
</form>
