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

<!doctype html>
<html lang="en">
<head>
	<title>History Detail</title>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">

    <style>
      
      .footer-height{
        height: 150px;
        margin-bottom: 0px;
      }

    </style>
</head>
<body>
	<?php 
        loadPublic(3); 
        $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
        if (!$conn->set_charset("utf8")) {
            printf("Error loading character set utf8: %s\n", $conn->error);
            exit();
        }
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $user_name = $_SESSION["username"];
        $sql = "select * from history where game_id = '".$id."' && (player1='".$user_name."' || player2='".$user_name."');";
        $result = $conn->query($sql);
        if($result->num_rows==0){
            header("location: History.php");
        }
        $row = $result->fetch_assoc();
        if($row){
            $game_name = $row["game_name"];
            $player1 = $row["player1"];
            $player2 = $row["player2"];
            $board_size = $row["board_size"];
        }

        $sql = "select * from action where game_id='".$id."' && step >= 0 ORDER BY step ASC;";
        $result = $conn->query($sql);
        $num_rows = $result->num_rows;
        echo "<div class='container p-4'>";
        $row = $result->fetch_assoc();
        $data[$num_rows][2];
        $i = 0;
        while($row){
            $data[$i][0] = $row["step"];
            $data[$i][1] = $row["action"];
            $i += 1;
            $row = $result->fetch_assoc();
        }
        
    ?>

	<?php
        echo "<form method='post'>";
        echo "<div class='row justify-content-center'>";
        echo "<div class='col-sm-0'><input class='btn btn-outline-secondary' type='submit' value='First' name='first'/></div>";
        echo "<div class='col-sm-0'><input class='btn btn-outline-secondary' type='submit' value='Previous' name='prev' /></div>";
        echo "<div class='col-sm-0'><input class='btn btn-outline-secondary' type='submit' value='Next' name='next' /></div>";
        echo "<div class='col-sm-0'><input class='btn btn-outline-secondary' type='submit' value='End' name='end' /></div>";
        echo "</div>";
        echo "</form>";

        if(isset($_POST["first"])){
            $_SESSION["step"] = 0;
        }else if(isset($_POST["prev"])){
            if($_SESSION["step"]>=0){
                $_SESSION["step"] = $_SESSION["step"]-1;
            }
        }else if(isset($_POST["next"]) && $_SESSION["step"] < $data[$num_rows-1][0]){
            $_SESSION["step"] = $_SESSION["step"]+1;
        }else if(isset($_POST["end"])){
            $_SESSION["step"] = $data[$num_rows-1][0];
        }

    ?>
    <?php
        echo "<div class='row justify-content-center'>";
        echo "<div class='col-sm-0 order-2'><table class='table table-bordered'><thead>";
        echo "<tr><td>$player1</td><td>$player2</td></tr>";
        echo "<tbody>";
        for($i=0;$i<$num_rows;$i++){
            if($i==0 || ($data[$i][0]%2==0 && $data[$i-1][0]%2==1)){
                echo "<tr>";
            }
            if($i==0 || $data[$i][0]!=$data[$i-1][0]){
                echo "<td>";
            }
            $x = (int)($data[$i][1]/$board_size);
            $y = $data[$i][1]%$board_size;
            echo "($x, $y)";
            if($i==$num_rows-1 || $data[$i][0]!=$data[$i+1][0]){
                echo "</td>";
            }
            if($i==$num_rows-1 || ($data[$i][0]%2==1 && $data[$i+1][0]%2==0)){
                echo "</tr>";
            }
        }
        $step = $_SESSION["step"];
        echo "</tbody></table>";
        echo "</div>";
        echo "<div class='col-sm-0 order-1'><iframe src='show_board.php?id=$id&step=$step' id='show_board' height=405 width=405 name='img'></div>";
        echo "</div>";
        echo "</div>";
        
        echo "<script src=./HistoryController.js></script>";
	?>

</body>
</html>