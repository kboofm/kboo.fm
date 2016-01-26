<?php
$classes = [
  "rating-{$event['rating']}",
];

if ($event['always_include']):
  $classes[] = "livewire-override";
endif;

$classes = implode(' ', $classes);
?>
<div class="checkbox livewire-event margin-vertical-md <?php print $classes; ?>">
  <label>
    <input checked="checked"
           name="<?php print $checkbox_name; ?>[]"
           id="<?php print "{$checkbox_name}-{$event['nid']}"; ?>"
           value="<?php print $event['nid']; ?>"
           type="checkbox">

    <?php
    $verbs = [
      'Hear',
      'Listen to',
    ];

    $random_index = array_rand($verbs);
    print "{$verbs[$random_index]} {$event['title']} @ {$event['time']} at {$event['venue']}";
    ?>



    <span class="rating">(Rating: <?php print $event['rating']; ?>)</span>
    <?php print $event['notes']; ?>
  </label>
</div>
