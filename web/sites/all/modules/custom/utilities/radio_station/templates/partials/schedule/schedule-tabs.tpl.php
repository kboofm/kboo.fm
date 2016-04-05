<ul class="nav nav-tabs"
    role="tablist">

  <li role="presentation">
    <a href="#tab-schedule-shows"
       role="tab"
       data-toggle="tab">
      Shows
    </a>
  </li>

  <li role="presentation"
    class="active">

    <a href="#tab-schedule-day"
       role="tab"
       data-toggle="tab">
      Day
    </a>
  </li>

  <li role="presentation">
    <a href="#tab-schedule-week"
       role="tab"
       data-toggle="tab">
      Week
    </a>
  </li>

</ul>


<div id="tabs-schedule" class="tab-content">
  <div role="tabpanel"
       class="tab-pane"
       id="tab-schedule-shows">

    <?php include 'scheduled-shows.tpl.php'; ?>
  </div>

  <div role="tabpanel"
       class="tab-pane active"
       id="tab-schedule-day">

    <?php include 'scheduled-day.tpl.php'; ?>
  </div>

  <div role="tabpanel"
       class="tab-pane"
       id="tab-schedule-week">

    <?php include 'scheduled-week.tpl.php'; ?>
  </div>
</div>
