<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$time=$sensor->time;
	$time=$time-3600;
	echo date('d-m-Y h:m:s',$time);
?>
