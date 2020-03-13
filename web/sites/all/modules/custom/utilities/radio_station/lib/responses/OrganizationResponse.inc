<?php

include_once('Response.inc');
class OrganizationResponse extends Response {

  public function getSponsors() {
    $this->template_name = 'radio_template_underwriters';

    $component = new OrganizationComponent();
    $sponsors = $component->getSponsors();

    $data = [
      'sponsors' => $sponsors,
    ];
    $this->addTemplateData($data);
    return $this->renderHtml();
  }
}
