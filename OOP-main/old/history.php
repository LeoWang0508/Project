<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
?>

<html>
<head>
	<title>History</title>
	<link rel='stylesheet' type='text/css' href='./style/public.css'>
	<link rel='stylesheet' type='text/css' href='./style/history.css'>
</head>
<body>
	<?php 
		loadPublic(); 
		session_start();
		$_SESSION["step"] = 1;
	?>
	<div class="title">
		<h1 align="center">History</h1>
	</div>
	
	<div class="main" align="center">
		<table class="rankTable">
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
						echo "<td><a href='history_detail.php?id=$game_id'>".$row["game_name"]."</a></td>";
						echo "<td>".$row["player1"]."</td>";
						echo "<td>".$row["player2"]."</td>";
						echo "<td>".$row["time"]."</td>";
						echo "<td>".$row["board_size"]."</td>";
						echo "</tr>";
						$row = $result->fetch_assoc();
					}
				?>
			</tbody>
		</table>
	</div>

</body>
</html>