<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$turbidity=$sensor->turbidity;
	$tb=$sensor->turbidity;
	$tb=$tb/30;
	echo '<div class="progress-bar bg-info" role="progressbar"
			style="width: '.$tb.'%'.'" aria-valuenow="50" aria-valuemin="0"
		aria-valuemax="100"></div>'
?>
