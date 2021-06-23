<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$turbidity=$sensor->turbidity;
	echo $turbidity;
?>
