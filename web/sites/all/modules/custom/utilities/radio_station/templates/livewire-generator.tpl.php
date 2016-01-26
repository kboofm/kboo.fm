<?php
if (!isset($phase)) {
  return;
}

switch ($phase) {
  case ELivewireRoutePhase::EventForm:
    include 'partials/livewire-events-form.tpl.php';
    break;
  case ELivewireRoutePhase::ScriptForm:
    include 'partials/livewire-script-form.tpl.php';
    break;
  case ELivewireRoutePhase::GeneratedScript:
    include 'partials/livewire-generated-script.tpl.php';
    break;
}
