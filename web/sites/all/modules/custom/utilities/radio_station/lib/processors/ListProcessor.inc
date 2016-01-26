<?php

class ListProcessor extends TemplateProcessor {
  public function process($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      $unwrapped = $entity->value();
      $nodes[] = [
        'url' => $this->getEntityUrl($unwrapped),
        'title' => $this->getTeaserTitle($entity),
      ];
    }

    usort(
      $nodes,
      function ($a, $b) {
        $left = strtolower($a['title']);
        $right = strtolower($b['title']);
        return strnatcmp($left, $right);
      }
    );

    return $nodes;
  }


  public function processSelect2($nids) {
    $nodes = [];

    foreach ($nids as $nid) {
      $entity = entity_metadata_wrapper('node', $nid);

      # 'id', and 'text' are keys expected by Select2
      $nodes[] = [
        'id' => $entity->getIdentifier(),
        'text' => $entity->title->value(),
      ];
    }

    usort(
      $nodes,
      function ($a, $b) {
        $left = strtolower($a['text']);
        $right = strtolower($b['text']);
        return strnatcmp($left, $right);
      }
    );

    return $nodes;
  }
}
