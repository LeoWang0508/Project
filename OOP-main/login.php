<?php
    $servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";

    session_start();
    $username = trim($_POST["uname"]);
    $password = trim($_POST["pswd"]);
    
    $_SESSION["username_err"] = false;
    $_SESSION["password_err"] = false;
    if(empty($username)){
        $_SESSION["username_err"] = "Please enter a username";
        header("location: ./Home.php");	
    }
    if(empty($password)){
        $_SESSION["password_err"] = "Please enter a password";
        header("location: ./Home.php");	
    }
    $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
    if($_SESSION["username_err"]==false && $_SESSION["password_err"]==false){
        $sql = "select * from users where username = '".$username."';";
        $result = $conn->query($sql);
        $row = $result->fetch_assoc();
        if($result->num_rows != 0 && password_verify($password, $row["password"])){
            $_SESSION["login"] = true;
            $_SESSION["username"] = $username;   
            header("location: ./Home.php");						
        }else {
            $_SESSION["username_err"] = "wrong username or password";
            $_SESSION["password_err"] = "wrong username or password";  
            header("location: ./Home.php");	   
        }
    }
    
?>