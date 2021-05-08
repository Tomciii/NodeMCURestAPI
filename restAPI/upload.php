<?php

define('DB_HOST', '10.101.20.1');
define('DB_USER', 'horvath');
define('DB_PASS', 'RaeGhei4juw0');
define('DB_DB', 'horvath');

$conn = new mysqli(DB_HOST,DB_USER,DB_PASS,DB_DB);

$id = ($_GET["id"]);
$temperature = ($_GET["temperature"]);
$humidity = ($_GET["humidity"]);

$insertString = 'insert into horvath.bun values("'.$id.'",now(), '.$humidity.','.$temperature.')';


if(mysqli_query($conn, $insertString)){
    print_r("New record created successfully.");
}
else
{
    print_r("Something went wrong 2</br>");
}

$select = 'select * from horvath.bun order by DateTime desc limit 20;';

$result = mysqli_query($conn, $select);



while($rows = mysqli_fetch_assoc($result)) {
    echo "Row: ".$rows["DateTime"]."   ".$rows["ID"]."   ".$rows["Temperature"]."   ".$rows["Humidity"]."</br>";
}

?>