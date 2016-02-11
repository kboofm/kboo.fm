<div class="row margin-top schedule-toolbar">
  <div class="col-xs-2 schedule-carousel-prev"
       data-carousel="<?php print $scheduled_week['id']; ?>">
    <i class="fa fa-arrow-left cursor-pointer schedule-trigger"></i>
  </div>


  <div class="col-xs-8 text-center">
    Week Beginning
    <span data-bind="datetime">
      <?php print $scheduled_week['datetime']; ?>
    </span>
  </div>


  <div class="col-xs-2 schedule-carousel-next"
       data-carousel="<?php print $scheduled_week['id']; ?>">
    <i class="fa fa-arrow-right cursor-pointer schedule-trigger pull-right"></i>
  </div>
</div>


<div class="row margin-top">
  <div id="<?php print $scheduled_week['id']; ?>"
       class="col-md-12 schedule-carousel"
       data-stream="<?php print $scheduled_week['stream']; ?>"
       data-type="<?php print $scheduled_week['type']; ?>">

    <div class="schedule-carousel-timestamp"
         data-timestamp="<?php print $scheduled_week['timestamp']; ?>">
    </div>

    <?php $loopIndex = 0; ?>
    <?php foreach ($scheduled_week['data'] as $dayOfWeek => $data_items): ?>
      <div class="weekdays<?php if ($loopIndex > 0): ?> cull<?php endif; ?>">
        <h4 data-bind="schedule-dayofweek">
          <?php print $dayOfWeek; ?>
        </h4>

        <ul class="list-group"
            data-bind="schedule-item">

          <?php foreach ($data_items as $schedule_item): ?>
            <li class="list-group-item">

              <?php
              $schedule_url = NULL;
              if (isset($schedule_item['url'])):
                $schedule_url = $schedule_item['url'];
              endif;
              ?>

              <div>
                <a data-bind="title-link"
                   href="<?php print $schedule_url; ?>">
                  <?php print $schedule_item['title']; ?>
                </a>

                <div data-bind="formatted-date">
                  <?php print $schedule_item['start']['formatted_date']; ?>
                </div>

                <div data-bind="formatted-time">
                <span data-bind="start-time">
                  <?php print $schedule_item['start']['formatted_time']; ?>
                </span>

                  -

                <span data-bind="finish-time">
                  <?php print $schedule_item['finish']['formatted_time']; ?>
                </span>
                </div>
              </div>
            </li>
          <?php endforeach; ?>
        </ul>
      </div>
      <?php $loopIndex++; ?>
    <?php endforeach; ?>

  </div>
</div>
