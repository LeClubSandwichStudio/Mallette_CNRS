<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$ph=$sensor->ph;
	$ph=$sensor->ph;
	$ph=$ph*7;
	echo '<div class="progress-bar bg-success" role="progressbar"
			style="width: '.$ph.'%'.'" aria-valuenow="14" aria-valuemin="0" aria-valuemax="14">
		</div>'
?>
