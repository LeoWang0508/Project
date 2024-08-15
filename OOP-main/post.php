<?php
    $servername = "localhost";
    $dbusername = "ooproject";
    $dbpassword = "ooproject";
    $dbname = "oop";
    session_start();
    $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
    if(isset($_POST["detail"]) && strlen($_POST["detail"])>5){
        $detail = $_POST["detail"];
        if(isset($_POST["tital"])){
            $tital = $_POST["tital"];
            $sql = "INSERT INTO forum (game_name, user, tital, detail) VALUES ('".$_POST["game_name"]."','".$_SESSION["username"]."','".$_POST["tital"]."','".$_POST["detail"]."');";
            $conn->query($sql);
            header("location: Forum.php");
        }else{
            $sql = "INSERT INTO forum (parent_id, user, detail) VALUES ('".$_SESSION["forum_id"]."','".$_SESSION["username"]."','".$_POST["detail"]."');";
            $conn->query($sql);
            header("location: forum_detail.php?id=".$_SESSION['forum_id']);
        }
    }
    if(isset($_POST["game_name"])){
        header("location: Forum.php");
    }else{
        header("location: forum_detail.php?id=".$_SESSION['forum_id']);
    }
?>