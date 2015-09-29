<?php
namespace KBOO\SpinUp;

class DefaultVariables {
  /**
   * Constructor
   */
  public function __construct() {
    variable_set('site_name', 'KBOO');
    variable_set('site_mail', 'no-reply@c4tech.com');
    variable_set('reroute_email_address', 'webnotifications@c4tech.com');
    variable_set('reroute_email_enable', 1);
    variable_set('reroute_email_enable_message', 1);
  }
}

new DefaultVariables();