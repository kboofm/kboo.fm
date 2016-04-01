<div id="node-<?php print $node->nid; ?>"
     class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>


  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>


  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_lead_image']);
      hide($content['field_more_images']);
      hide($content['field_authored_by']);
      hide($content['field_hosted_by']);
      hide($content['field_produced_by']);

      print theme('radio_template_program_scheduled_timeslots');
      print render($content['field_authored_by']);
    ?>


    <div class="node-images">
      <?php
        print render($content['field_lead_image']);
        print render($content['field_more_images']);
      ?>
    </div>


    <?php
      print render($content['field_hosted_by']);
      print render($content['field_produced_by']);
      print theme('radio_template_program_podcast_link');
      print render($content);
      print theme('radio_template_program_upcoming_episodes');
      print theme('radio_template_program_content_list');
    ?>
  </div>


  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>
</div>
