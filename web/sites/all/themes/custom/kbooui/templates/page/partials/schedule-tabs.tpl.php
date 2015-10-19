<ul class="nav nav-tabs" role="tablist">
  <li role="presentation" class="active">
    <a href="#shows" role="tab" data-toggle="tab">Shows</a>
  </li>
  <li role="presentation">
    <a href="#day" role="tab" data-toggle="tab">Day</a>
  </li>
  <li role="presentation">
    <a href="#week" role="tab" data-toggle="tab">Week</a>
  </li>
</ul>

<div class="tab-content">
  <div role="tabpanel" class="tab-pane active" id="shows">
    <?php include 'scheduled-shows.tpl.php'; ?>
  </div>

  <div role="tabpanel" class="tab-pane" id="day">
    <?php include 'scheduled-day.tpl.php'; ?>
  </div>

  <div role="tabpanel" class="tab-pane" id="week">
    <?php include 'scheduled-week.tpl.php'; ?>
  </div>
</div>
