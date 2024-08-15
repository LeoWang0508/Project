<?php
    $servername = "localhost";
    $dbusername = "ooproject";
    $dbpassword = "ooproject";
    $dbname = "oop";
    session_start();

    $username = $_POST["uname"];
    $password = $_POST["password"];
    $confirm_password = $_POST["confirm_password"];

    if(empty($username)){
        $_SESSION["username_err"] = "Please enter a username";
        header("location: ./Home.php");	
    }
    if(empty($password) || empty($confirm_password)){
        $_SESSION["password_err"] = "Please enter a password";
        header("location: ./Home.php");	
    }
    $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
    $sql = "SELECT * FROM users WHERE username = '".$username."';";
    $result = $conn->query($sql);
    if($result->num_rows > 0){
        $_SESSION["username_err"] = "This username was taken";
        header("location: ./Home.php");	
    }
    if($password!=$confirm_password){
        $_SESSION["password_err"] = "Password did not match";
        header("location: ./Home.php");	
    }
    $hash_password = password_hash($password, PASSWORD_DEFAULT);
    $sql = "INSERT INTO users (user_id, username, password) VALUES (NULL,'".$username."','".$hash_password."');";
    $conn->query($sql);
    $_SESSION["username_err"] = "Success!";
    header("location:./Home.php");

?>