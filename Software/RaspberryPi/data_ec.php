<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$ec=$sensor->ec;
	echo $ec;
?>
