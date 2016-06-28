<?php

class RadioRoles {
  public static function has($role, $include_admin = false) {
    return RadioRoles::hasAny([$role], $include_admin);
  }


  public static function hasAny(array $roles, $include_admin = false) {
    global $user;

    if ($user->uid == 1) {
      return $include_admin;
    }

    $user_roles = array_values($user->roles);
    $check = array_intersect($roles, $user_roles);
    $has_role = !empty($check);

    return $has_role;
  }


  public static function hasAll(array $roles, $include_admin = false) {
    global $user;

    if ($user->uid == 1) {
      return $include_admin;
    }

    $user_roles = array_values($user->roles);
    return ($roles == $user_roles);
  }


  public static function hasOnly($role, $include_admin = false) {
    global $user;

    if ($user->uid == 1) {
      return $include_admin;
    }

    $user_roles = array_values($user->roles);
    $diff = array_diff($user_roles, [$role]);
    return empty($diff);
  }
}
