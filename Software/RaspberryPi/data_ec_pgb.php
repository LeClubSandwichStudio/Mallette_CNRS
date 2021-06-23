<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$ec=$sensor->ec;
	$ec=$sensor->ec;
	$ec=$ec*1000;
	echo '<div class="progress-bar bg-warning" role="progressbar"
			style="width: '.$ec.'%'.'" aria-valuenow="50" aria-valuemin="0"
			aria-valuemax="100"></div>'
?>
