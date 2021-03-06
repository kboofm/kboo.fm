<div class="row margin-top schedule-toolbar">
  <div class="col-xs-2 schedule-carousel-prev"
       data-carousel="<?php print $scheduled_shows['id']; ?>">
    <i class="fa fa-arrow-left cursor-pointer schedule-trigger"></i>
  </div>


  <div class="col-xs-8 text-center"
       data-bind="datetime">
    <?php print $scheduled_shows['datetime']; ?>
  </div>


  <div class="col-xs-2 schedule-carousel-next"
       data-carousel="<?php print $scheduled_shows['id']; ?>">
    <i class="fa fa-arrow-right cursor-pointer schedule-trigger pull-right"></i>
  </div>
</div>


<div class="row margin-top">
  <div id="<?php print $scheduled_shows['id']; ?>"
       class="col-sm-12 schedule-carousel"
       data-stream="<?php print $scheduled_shows['stream']; ?>"
       data-type="<?php print $scheduled_shows['type']; ?>">

    <div class="schedule-carousel-timestamp"
         data-timestamp="<?php print $scheduled_shows['timestamp']; ?>">
    </div>

    <ul class="list-group">

      <?php foreach ($scheduled_shows['data'] as $schedule_item): ?>
        <li class="list-group-item"
            data-bind="schedule-item">

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
</div>
