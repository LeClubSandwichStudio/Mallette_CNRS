<?php
$strList = explode(" ", file_get_contents("data/commandeWeb.txt"));
$id = $strList[0];

if(isset($_POST["Start"])){
    $id = $id + 1;
    file_put_contents("data/commandeWeb.txt", $id.",start,".$_POST["Time"]);
}
else if(isset($_POST["Stop"])){
    $id = $id + 1;
    file_put_contents("data/commandeWeb.txt", $id.",stop");
}

?>
