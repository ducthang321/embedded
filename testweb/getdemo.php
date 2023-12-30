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

    if(!empty($_POST['nhietdo']) && !empty($_POST['doam']))
    {
    	$nhietdo = $_POST['nhietdo'];
    	$doam = $_POST['doam'];
        $doamdat = $_POST['doamdat'];

	    $sql = "INSERT INTO logs (doam, nhietdo,doamdat, Date, Time)
		
		VALUES ('".$doam."', '".$nhietdo."','".$doamdat."', '".$d."', '".$t."')";

		if ($conn->query($sql) === TRUE) {
		    echo "CẬP NHẬT THÀNH CÔNG";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>