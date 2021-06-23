<?php
    $value = file_get_contents("resistance.txt");
	$json=(json_decode($value));
	$sensor=$json->sensors;
	
	$tp=$sensor->temperature;
		while(i<10){
			$i++;
			$somme+=$tp;
			$moyenne=$somme/$i;
			sleep(0.2);
			
		}
		echo '<div class="h5 mb-0 mr-3 font-weight-bold text-gray-800">'.$moyenne.'</div>';
?>
