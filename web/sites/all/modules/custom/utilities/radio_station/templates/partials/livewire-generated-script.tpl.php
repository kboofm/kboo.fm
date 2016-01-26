<p class="margin-vertical-lg livewire-lead-text">
  <?php print $lead_in; ?>
  <?php print $display_date; ?>
</p>


<p class="margin-vertical-lg livewire-lead-text">
  <?php print $sponsor_info; ?>
</p>


<ul class="margin-vertical-lg">
  <?php
  foreach ($day_venues as $venue):
  ?>
    <li class="margin-bottom-sm">
      <?php
      include 'generated-script-venue.tpl.php';
      ?>
    </li>
  <?php
  endforeach;
  ?>
</ul>


<p class="margin-vertical-lg livewire-lead-text">
  <?php print $tomorrow_lead_in; ?>
</p>


<ul class="margin-vertical-lg">
  <?php
  foreach ($next_day_venues as $venue):
  ?>
    <li>
      <?php
      print $venue['title'];
      include 'generated-script-venue.tpl.php';
      ?>
    </li>
  <?php
  endforeach;
  ?>
</ul>


<p class="margin-vertical-lg livewire-lead-text">
  <?php print $lead_out; ?>
</p>
