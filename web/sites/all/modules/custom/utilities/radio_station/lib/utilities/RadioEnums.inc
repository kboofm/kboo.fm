<?php
abstract class EStreams {
  const One = 'Stream 1';
  const Two = 'Stream 2';
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


abstract class ELivewireRoutePhase {
  const EventForm = 0;
  const ScriptForm = 1;
  const GeneratedScript = 2;
}


abstract class ELivewireOverride {
  const None = 0;
  const AlwaysInclude = 1;
  const DontInclude = 2;
}


abstract class EDisplayStyle {
  const Small = 0;
  const Medium = 1;
}
