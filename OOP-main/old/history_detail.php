<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";

    session_start();
    $id = (int)$_GET[id];
    $_SESSION["id"] = $id;
    $game_name = NULL;
?>

<html>
<head>
	<title>History Detail</title>
	<link rel='stylesheet' type='text/css' href='./style/history_detail.css'>
    <link rel='stylesheet' type='text/css' href='./style/public.css'>
</head>
<body>
	<?php 
        loadPublic(); 
        $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
        if (!$conn->set_charset("utf8")) {
            printf("Error loading character set utf8: %s\n", $conn->error);
            exit();
        }
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $sql = "select * from history where game_id='".$id."';";
        $result = $conn->query($sql);
        $row = $result->fetch_assoc();
        if($row){
            $game_name = $row["game_name"];
            $player1 = $row["player1"];
            $player2 = $row["player2"];
            $board_size = $row["board_size"];
        }

        $sql = "select * from action where game_id='".$id."' && step >= 0 ORDER BY step ASC;";
        $result = $conn->query($sql);
        $row = $result->fetch_assoc();

        echo "<div class='table_loc'><table class='detail_table'><thead>";
        echo "<tr><td><div class='detail'>$player1</div></td><td><div class='detail'>$player2</div></td></tr>";
        echo "<tbody>";
        while($row){
            $x = (int)($row["action"]/$board_size);
            $y = $row["action"]%$board_size;
            if($row["step"]%2==0){
                echo "<tr><td><div class='detail'>($x, $y)</div></td>";
            }else{
                echo "<td><div class='detail'>($x, $y)</div></td></tr>";
            }
            $row = $result->fetch_assoc();
        }
        echo "</tbody></table></div>";
        
    ?>
	<div class="title">
		<h1 align="center"><?php echo $game_name ?> History</h1>
	</div>

	<?php

        echo "<div class='button'><form method='post'>";
        echo "<input type='submit' value='First' name='first'/>";
        echo "<input type='submit' value='Previous' name='prev' />";
        echo "<input type='submit' value='Next' name='next' />";
        echo "<input type='submit' value='End' name='end' />";
        echo "</form></div>";

        if(isset($_POST["first"])){
            $_SESSION["step"] = 1;
        }else if(isset($_POST["prev"])){
            if($_SESSION["step"]>0){
                $_SESSION["step"] = $_SESSION["step"]-1;
            }
        }else if(isset($_POST["next"])){
            $_SESSION["step"] = $_SESSION["step"]+1;
        }else if(isset($_POST["end"])){
            $_SESSION["step"] = 10000;
        }
        
        $step = $_SESSION["step"];

    ?>

    <div class="board">
    <?php
        echo "<iframe src='board.php?id=$id&step=$step' height=500 width=500 name='img'>";
	?>
    </div>

</body>
</html>