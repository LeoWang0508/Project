<?php
	include "public.php";
	$servername = "140.122.184.75";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
?>

<html>
<head>
	<title>Gobang</title>
	<link rel='stylesheet' type='text/css' href='./style/public.css'>
</head>
<body>
	<?php loadPublic(); ?>
	<div class="title">
		<h1 align="center">Gobang</h1>
	</div>

	<?php
		$id=2;
		$number=2;
		echo "<iframe src='board.php?id=$id&number=$number' height=500 width=500 name='img'>";
	?>
</body>
</html>