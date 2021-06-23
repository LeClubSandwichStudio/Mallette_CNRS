<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$tp=$sensor->temperature;
	echo '<div class="progress-bar bg-primary" role="progressbar"
			style="width: '.$tp.'%'.'" name="progressBarTemp" aria-valuenow="20" aria-valuemin="0"
			aria-valuemax="100">
		</div>';
?>
