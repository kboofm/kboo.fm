<ul class="nav nav-tabs" role="tablist">
  <li role="presentation" class="active">
    <a href="#up-next" role="tab" data-toggle="tab">Up Next</a>
  </li>
  <li role="presentation">
    <a href="#today" role="tab" data-toggle="tab">Today</a>
  </li>
  <li role="presentation">
    <a href="#this-week" role="tab" data-toggle="tab">This Week</a>
  </li>
  <li role="presentation">
    <a href="#next-week" role="tab" data-toggle="tab">Next Week</a>
  </li>
</ul>

<div class="tab-content">
  <div role="tabpanel" class="tab-pane active" id="up-next">
    <?php include 'scheduled-next.tpl.php'; ?>
  </div>

  <div role="tabpanel" class="tab-pane" id="today">
    <?php include 'scheduled-today.tpl.php'; ?>
  </div>

  <div role="tabpanel" class="tab-pane" id="this-week">
    <?php include 'scheduled-this-week.tpl.php'; ?>
  </div>

  <div role="tabpanel" class="tab-pane" id="next-week">
    <?php include 'scheduled-next-week.tpl.php'; ?>
  </div>
</div>
