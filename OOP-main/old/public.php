<?php
	session_start();
	$path = "";
	function loadPublic() {
		echo "
		<link rel='stylesheet' type='text/css' href='./style/public.css'>
		<div class='navbar'>
			<a class='navbartext' href='".$path."home.php'>Home</a>
			<a class='navbartext' href='".$path."games.php'>Lobby</a>
			<a class='navbartext' href='".$path."forum.php'>Forum</a>";
			
		if(isset($_SESSION["login"]) && $_SESSION["login"] === true){
			echo "<a class='navbarRighttext' href='".$path."logout.php'>Logout</a>";
			echo "<a class='navbartext' href='".$path."history.php'>History</a>";
		}
		else {
			echo "<a class='navbarRighttext' href='".$path."register.php'>Register</a>";
			echo "<a class='navbarRighttext' href='".$path."login.php'>Login</a>";
			echo "<a class='navbartext' href='".$path."login.php'>History</a>";
		}
		echo "</div>";
	}
?>