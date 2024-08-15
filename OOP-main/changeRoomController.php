<?php
    $servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
    $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);

    session_start();
    if(!isset($_GET["clear"])){
        $game = $_POST["games"];
        $board_size = $_POST["Board_Size"];
        $AI_Allowed = $_POST["AI_Allowed"];
        $Time_Limited = $_POST["Time_Limited"];
        $Regret = $_POST["Regret"];
        $player2 = "None";

        $sql = "select * from history where game_id = 1;";
        $result = $conn->query($sql);
        $row = $result->fetch_assoc();
        $id = $row["board_size"]+1;

        $sql = "UPDATE history set board_size=".$id." where game_id=1;";
        $conn->query($sql);

        $sql = "INSERT INTO history (game_id, game_name, player1, player2, board_size) VALUES ('".$id."', '".$game."','".$_SESSION['username']."','".$player2."',$board_size);";
        $conn->query($sql);

        array_push($_SESSION["rooms"], $id, $game, $_SESSION["username"], $board_size, $AI_Allowed, $Time_Limited, $Regret);
        $id += 1;
        header("location:http://140.122.184.75:4000/".$id."/1/".$_SESSION['username']."-Null");
    }else{
        $id = $_GET["id"];
        array_push($_SESSION["clearRooms"], $id);
        header("location:http://140.122.184.75/Home.php");
    }
    
?>