<?php include 'partials/pager.tpl.php'; ?>

<table class="table
              table-bordered
              table-condensed
              table-hover
              margin-top-md">
  <thead>
    <tr>
      <td>
        Title
      </td>

      <td>
        Event Date
      </td>

      <td>
        Venue
      </td>

      <td>
        Acts
      </td>

      <td>
        Edit
      </td>
    </tr>
  </thead>


  <tbody>
  <?php foreach ($pager['events'] as $event): ?>
    <tr>

      <td>
        <a href="<?php print $event['url']; ?>">
          <?php print $event['title']; ?>
        </a>
      </td>


      <td>
        <div>
          <?php print date("l", $event['event_date']); ?>
        </div>

        <div>
          <?php print date("F j", $event['event_date']); ?>
        </div>
      </td>


      <td>
        <?php if ($event['venue']): ?>
          <a href="<?php print $event['venue']['url']; ?>">
            <?php print $event['venue']['title']; ?>
          </a>
        <?php endif; ?>
      </td>


      <td>
        <?php $last = count($event['acts']) - 1; ?>
        <?php foreach ($event['acts'] as $index => $act): ?>
          <div>
            <a href="<?php print $act['url']; ?>">
              <?php print $act['title']; ?>
            </a>

            <?php
              if ($index < $last):
                print ", ";
              endif;
            ?>
          <div>
        <?php endforeach; ?>
      </td>

      <td>
        <a href="<?php print "/node/{$event['nid']}/edit"; ?>">
          Edit
        </a>
      </td>

    </tr>
  <?php endforeach; ?>
  </tbody>
</table>

<?php
include 'partials/pager.tpl.php';
