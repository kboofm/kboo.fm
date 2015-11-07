<?php

class UserMigration extends DrupalUser6Migration {

  /**
   * Prepare the source row
   *
   * @param $row
   * @return bool
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $anonymous_user = ($row->uid == 0);
    if ($anonymous_user) {
      return TRUE;
    }

    $active = ($row->status == 1);
    if (!$active) {
      return FALSE;
    }

    $one_month_ago = strtotime("-1 month");
    $old_enough = ($row->created >= $one_month_ago);
    $logged_in_before = ($row->access > 0);
    if ($old_enough && !$logged_in_before) {
      return FALSE;
    }

    return TRUE;
  }
}