<?php
abstract class EStreams {
  const One = 'one';

  public static function all() {
    return [
      EStreams::One,
    ];
  }
}


abstract class ELocationSearchOptions {
  const Street = 'thoroughfare';
  const City = 'locality';
  const Zip = 'postal_code';
}


abstract class EStringSearchOptions {
  const Contains = 0;
  const Equals = 1;
  const StartsWith = 2;
}


abstract class ENotificationCommentSave {
  const KEY = 'comment_save';
  const RECIPIENTS = 'radio_notifications_comment_save_recipients';
}


abstract class EShowHostStatus {
  const Active = 1;
  const InActive = 2;
  const Both = 3;
}


abstract class EDisplayStyle {
  const Small = 0;
  const Medium = 1;
}


abstract class EArchiveTypes {
  const Never = 0;
  const Temporary = 1;
  const Permanent = 2;
}


abstract class EProgramStatus {
  const Current = 0;
  const Retired = 1;
}
