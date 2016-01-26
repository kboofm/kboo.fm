<h4>On now:</h4>

<?php if (!$onair['data']): ?>
    <p class="margin-bottom-lg">
      Nothing airing
    </p>
<?php else: ?>
  <div class="row margin-top">
    <div class="col-md-12"
         data-stream="<?php print $onair['stream']; ?>"
         data-type="<?php print $onair['type']; ?>">

      <div class="schedule-carousel-timestamp"
           data-timestamp="<?php print $onair['timestamp']; ?>">
      </div>

      <ul class="list-group">
        <?php foreach ($onair['data'] as $schedule_item): ?>
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
<?php endif;

