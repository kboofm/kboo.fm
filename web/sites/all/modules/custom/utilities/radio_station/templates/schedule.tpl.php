<p class="margin-vertical-lg">
  Set your alarm for jazz in the morning and hit the pillow to sultry blues.
  Don't miss any of your favorite programs or show hosts!
</p>


<div class="row oz-schedule visible-xs">
  <div class="col-md-4 col-md-offset-4">
    <?php include "partials/schedule/schedule-tabs.tpl.php"; ?>
  </div>
</div>


<table class="table
              table-bordered
              table-condensed
              table-hover
              hidden-xs">
  <thead>
    <tr>
      <?php foreach ($schedule_calendar_columns as $col): ?>
        <td>
          <?php print $col; ?>
        </td>
      <?php endforeach; ?>
    </tr>
  </thead>


  <tbody>
    <?php foreach ($schedule_calendar as $hour => $item): ?>
      <tr>
        <td>
          <?php print $hour; ?>
        </td>

        <?php foreach ($item['days'] as $slot): ?>
          <?php
            if ($slot['overlapped']):
              continue;
            endif;
          ?>
          <td rowspan="<?php print $slot['length']; ?>">
            <?php if (isset($slot['url'])): ?>
              <a href="<?php print $slot['url']; ?>">
            <?php endif; ?>

                <?php print $slot['title']; ?>

            <?php if (isset($slot['url'])): ?>
              </a>
            <?php endif; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>