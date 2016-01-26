<?php
$first_verbs = [
  'Hear',
  'Listen to',
];

$second_verbs = [
  'followed by',
  'then hear',
];

$random_index = array_rand($first_verbs);
print $first_verbs[$random_index] . " ";

foreach ($venue['events'] as $index => $event):
    if ($index > 0):
      $random_index = array_rand($second_verbs);
      print " " . $second_verbs[$random_index] . " ";
    endif;

    $time = Helpers::toCarbonString('g:i', $event['starttime']);
    print "{$event['title']} @ {$time}";
endforeach;

print " at {$venue['title']}";
