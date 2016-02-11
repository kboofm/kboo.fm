<?php

class UserMigration extends DrupalUser6Migration {

  /**
   * Query
   *
   * @return \QueryConditionInterface
   */
  protected function query() {
    $query = parent::query();
    $query->condition('u.status', 1, '=');

    $one_month_ago = strtotime("-1 month");
    $logged_in_before = new DatabaseCondition('AND');
    $logged_in_before->condition('u.created', $one_month_ago, '>=');
    $logged_in_before->condition('u.access', 0, '>');

    $new_users = new DatabaseCondition('AND');
    $new_users->condition('u.created', $one_month_ago, '<');

    $or = new DatabaseCondition('OR');
    $or->condition($logged_in_before);
    $or->condition($new_users);

    $query->condition($or);
    return $query;
  }
}