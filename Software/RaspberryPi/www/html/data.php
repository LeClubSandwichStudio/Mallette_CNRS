<?php
  $data = file_get_contents("data/data.txt");
  $cmd = file_get_contents("data/commandeWeb.txt");
  
  $arr = array($data, $cmd);

  echo json_encode($arr);
?>
