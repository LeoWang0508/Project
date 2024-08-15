<?php
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>

    <title>Histroy</title>

  </head>
  <body>

    <?php
      include "public.php";
      loadPublic(3);
      session_start();
      $_SESSION["step"] = 0;
    ?>
    
    <div class="container-sm" style="height: 550px">
      <table class="table table-striped">
        <thead>
          <tr>
            <th>Game</th>
            <th>Player1</th>
            <th>Player2</th>
            <th>Time</th>
            <th>Board Size</th>
          </tr>
        </thead>
        <tbody>
          <?php
            $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
            if (!$conn->set_charset("utf8")) {
              printf("Error loading character set utf8: %s\n", $conn->error);
              exit();
            }
            if ($conn->connect_error) {
              die("Connection failed: " . $conn->connect_error);
            } 
            $user_name = $_SESSION["username"];
            $sql = "select * from history where player1='".$user_name."' || player2='".$user_name."';";
            $result = $conn->query($sql);
            $row = $result->fetch_assoc();
            while($row) {
              $game_id = $row["game_id"];
              echo "<tr>";
              echo "<td id='history_detail'><a href='history_detail.php?id=$game_id'>".$row["game_name"]."</a></td>";
              echo "<td>".$row["player1"]."</td>";
              echo "<td>".$row["player2"]."</td>";
              echo "<td>".$row["time"]."</td>";
              echo "<td>".$row["board_size"]."</td>";
              echo "</tr>";
              $row = $result->fetch_assoc();
            }
            echo "<script src=./HistoryController.js></script>";
          ?>
        </tbody>
      </table>
    </div>


  <?php
    loadFooter();
  ?>


  </body>
</html>