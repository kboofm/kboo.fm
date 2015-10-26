<div class="row margin-top schedule-toolbar">
  <div class="col-md-1 schedule-carousel-prev"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-left cursor-pointer schedule-trigger"></i>
  </div>


  <div class="col-md-1 schedule-carousel-next"
       data-carousel="<?php print $schedule['id']; ?>">
    <i class="fa fa-arrow-right cursor-pointer schedule-trigger"></i>
  </div>

  <div class="col-md-10"
       data-bind="datetime">
    <?php print $schedule['datetime']; ?>
  </div>
</div>


<div class="row margin-top">
  <div id="<?php print $schedule['id']; ?>"
       class="col-md-12 schedule-carousel"
       data-stream="<?php print $schedule['stream']; ?>"
       data-type="<?php print $schedule['type']; ?>">

    <div class="schedule-carousel-timestamp"
         data-timestamp="<?php print $schedule['timestamp']; ?>">
    </div>

    <ul class="list-group">

      <?php foreach ($schedule['data'] as $schedule_item): ?>
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
