<?php
  $data = file_get_contents("data/data.txt");

  echo json_encode($data);
?>
