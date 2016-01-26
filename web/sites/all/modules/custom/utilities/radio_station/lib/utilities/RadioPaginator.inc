<?php

class RadioPaginator {
  public static function paginate($page, $total_count, $per_page = 10) {
    $first = 1;
    $last = ceil($total_count / $per_page);

    $prev = null;
    if ($page - 1 >= $first) {
      $prev = $page - 1;
    }

    $next = null;
    if ($page + 1 <= $last) {
      $next = $page + 1;
    }

    $first_shown = floor($page / 10) * 10;
    $first_shown = ($first_shown < $first) ? $first : $first_shown;

    $last_shown = ceil($page / 10) * 10;
    $last_shown = ($last_shown > $last + 1) ? $last : $last_shown - 1;

    if ($last == $page || $last == $next) {
      $last = null;
    }

    return [
      'query_string' => RadioPaginator::getQueryString(),
      'current' => $page,
      'first' => $first,
      'last' => $last,
      'prev' => $prev,
      'next' => $next,
      'first_shown' => $first_shown,
      'last_shown' => $last_shown,
    ];
  }


  public static function alphabetic($data, $current = null, $filter = true, $anchor = true, $key = 'title') {
    $alphabet = range('A', 'Z');
    $links = array_combine($alphabet, $alphabet);
    $misc['#'] = '#';
    $links = $misc + $links;

    if (!empty($current)) {
      if (in_array($current, $alphabet)) {
        $current = $current[0];
      } else {
        $current = '#';
      }
    }

    if ($filter) {
      # filter out keys with no data
      $links = array_filter(
        $links,
        function ($item) use ($data) {
          return isset($data[$item]) && count($data[$item]) > 0;
        }
      );
    }

    $links = array_map(
      function ($item) use ($current, $key, $anchor) {
        $active = ($item == $current);

        if ($anchor) {
          $href = "#{$item}";
        } else {
          $href = "?{$key}={$item}";
        }

        return [
          'active' => $active,
          'key' => $key,
          'value' => $item,
          'title' => $item,
          'href' => $href,
        ];
      },
      $links
    );

    return $links;
  }


  private static function getQueryString() {
    $query_string = Helpers::getQueryString();
    $pos = strpos($query_string, 'page=');
    if ($pos !== false) {
      $query_string = substr($query_string, 0, $pos);
    }

    if ($query_string == 'begins=') {
      $query_string = '';
    }

    if ($query_string) {
      $query_string .= "&";
    }

    return $query_string;
  }
}
