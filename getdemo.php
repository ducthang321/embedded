<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "ducthang";
    $dbname = "espdemo";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    //Get current date and time
    date_default_timezone_set('Asia/Ho_Chi_Minh');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");

    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
    	$nhietdoc = $_GET['nhietdoc'];
    	$nhietdof = $_GET['nhietdof'];
        $doam = $_GET['humidityTemp'];

	    $sql = "INSERT INTO logs (nhietdoc,nhietdof,doam, Date, Time)
		
		VALUES ('".$nhietdoc."','".$nhietdof."','".$doam."', '".$d."', '".$t."')";

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>