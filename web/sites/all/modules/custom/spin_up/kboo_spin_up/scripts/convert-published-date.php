<?php

class ConvertPublishedDate {
  private $data;

  /**
   * Load data
   *
   */
  private function loadData() {
    echo "Loading data..." . PHP_EOL;

    $fieldname = "field_published_date";
    $fpd_table = "field_data_{$fieldname}";

    $query = db_select("node", "n");
    $query->leftJoin(
      $fpd_table,
      $fpd_table,
      "n.nid = {$fpd_table}.entity_id"
    );

    $query->addField("n", "nid");
    $query->addField("n", "created");
    $query->addField(
      $fpd_table,
      "{$fieldname}_value",
      $fieldname
    );

    $this->data = $query->execute()->fetchAllAssoc('nid');
  }


  /**
   * Save to publicate_date table
   *
   */
  private function convert() {
    $cnt = count($this->data);
    $index = 0;

    foreach ($this->data as $datum) {
      $index++;
      echo "({$index}/{$cnt}) Converting data..." . PHP_EOL;

      $timestamp = $datum->created;
      if ($datum->field_published_date) {
        $timestamp = strtotime($datum->field_published_date);
      }

      $key = ['nid' => $datum->nid];
      $fields = ['published_at' => $timestamp];

      db_merge('publication_date')
        ->key($key)
        ->fields($fields)
        ->execute();
    }
  }


  /**
   * Execute the script
   */
  public function execute() {
    $this->loadData();
    $this->convert();
    echo PHP_EOL;
    echo PHP_EOL;
  }
}


$converter = new ConvertPublishedDate();
$converter->execute();
