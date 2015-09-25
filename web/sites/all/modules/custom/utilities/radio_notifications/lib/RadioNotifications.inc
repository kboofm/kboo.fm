<?php

abstract class RadioNotificationCommentSave {
  const KEY = 'comment_save';
  const RECIPIENTS = 'radio_notifications_comment_save_recipients';
}


class RadioNotifications {
  /**
   * Send comment save email
   *
   * @param $comment
   */
  public static function commentSendEmail($comment) {
    drupal_mail(
      $module = 'radio_notifications',
      $key = RadioNotificationCommentSave::KEY,
      $to = NULL,
      $language = 'und',
      $params = ['comment' => $comment]
    );
  }


  /**
   * Define variables for the module
   *
   * @return mixed
   */
  public static function defineVariables() {
    $variables[RadioNotificationCommentSave::RECIPIENTS] = [
      'title' => t('Comment saved recipients'),
      'description' => t(
        'List of email address whom to send notifications upon comment saved'
      ),
      'default' => [
        'webnotifications@c4tech.com',
      ],
    ];

    return $variables;
  }


  /**
   * Define an email according to $key
   *
   * @param $key
   * @param $message
   * @param $params
   */
  public static function defineEmail($key, &$message, $params) {
    if ($key == RadioNotificationCommentSave::KEY) {
      RadioNotifications::defineEmailCommentSave($message, $params);
    }
  }


  /**
   * Define an email for comment save
   * @param $message
   * @param $params
   */
  public static function defineEmailCommentSave(&$message, $params) {
    $comment = $params['comment'];

    $front = '<front>';
    $homepage_url = url($front, ['absolute' => TRUE]);
    $comment_admin_url = "{$homepage_url}admin/comment/approval";


    // Email subject
    $message['subject'] = t('New Comment recieved');


    // Email to
    $to = variable_get_value(RadioNotificationCommentSave::RECIPIENTS);
    if (is_array($to)) {
      $to = implode(', ', $to);
    }
    $message['to'] = $to;


    // Email body - admin url to approve comment
    $message['body'][] = t(
      'Approve comment here: @comment_admin_url',
      [
        '@comment_admin_url' => $comment_admin_url,
      ]
    );


    // Email body - comment subject
    $message['body'][] = t(
      'Comment subject: @subject',
      [
        '@subject' => $comment->subject,
      ]
    );


    // Email body - comment content
    $message['body'][] = t('');
    $message['body'][] = t('Comment content below');
    $message['body'][] = t('---------------');
    $message['body'][] = t(
      '@content,',
      [
        '@content' => $comment->comment_body['und'][0]['value'],
      ]
    );
  }
}