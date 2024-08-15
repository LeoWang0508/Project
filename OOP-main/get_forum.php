<?php
    session_start();
    if($_POST["game_name"]=="All" || !isset($_POST["game_name"])){
        $sql = "select * from forum where parent_id is NULL;";
    }else{
        $sql = "select * from forum where game_name='".$_POST["game_name"]."' and parent_id is NULL;";
    }
    $_SESSION['result'] = $sql;
    header("location: Forum.php");
?>