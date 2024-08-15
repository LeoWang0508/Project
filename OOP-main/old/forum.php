<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
?>

<html>
<head>
	<title>Forum</title>
	<link rel='stylesheet' type='text/css' href='./style/public.css'>
	<link rel='stylesheet' type='text/css' href='./style/forum.css'>
</head>
<body>
	<?php 
		loadPublic(); 
		session_start();
		$conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
        if (!$conn->set_charset("utf8")) {
            printf("Error loading character set utf8: %s\n", $conn->error);
            exit();
        }
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
	?>
	<div class="title">
		<h1 align="center">Forum</h1>
	</div>

	<div align="center">
		<table>
			<tbody>
				<?php
					if($_SESSION["login"]==true){
						echo "<form method='post'>";
						echo "<tr><td><div class='text'>Tital</div></td></tr>";
						echo "<tr><td><div class='text'><input type='text' name='title' style='width:500px;'></div></td></tr>";
						echo "<tr><td><div class='text'>Detail</div></td></tr>";
						echo "<tr><td><div class='text'><textarea name='detail' cols='70' rows='10'></textarea></div></td></tr>";
						echo "</form>";
						if(isset($_POST["enter"])){
							if($_POST["title"]!='' && $_POST["detail"]!=''){
								$sql = "insert into forum (forum_id, title, user, word) values (NULL, ".$_POST['tital'].", ".$_SESSION['username'].", ".$_POST['detail'].")";
								$result = $conn->query($sql);
								$row = $result->fetch_assoc();

							}else{
								$_SESSION["forum_error"] = 1;
							}
						}
						if($_SESSION["forum_error"]==1){
							$_SESSION["forum_error"] = 0;
							echo "<tr><td><div class='text'>title or detail cannot be empty</div></td></tr>";
						}
						echo "<tr><td><div class='text'><input type='submit' name='enter' value='enter'></textarea></div></td></tr>";
						
						
					}

				?>
			</tbody>
		</table>
	</div>

</body>
</html>