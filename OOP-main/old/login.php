<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
?>

<?php
	session_start();
	if(isset($_SESSION["login"]) && $_SESSION["login"] === true){
		header("location: home.php");
		exit;
	}
?>

<html>
<head>
	<title>Login</title>
	<link rel='stylesheet' type='text/css' href='./style/public.css'>
</head>
<body>

	<?php loadPublic(); ?>

	<div class="title">
		<h1 align="center">Login</h1>
	</div>
	
	<div class="main" align="center">
		
		<?php
			$username = $password = $confirm_password = "";
			$username_err = $password_err = $confirm_password_err = "";
			$conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
			if (!$conn->set_charset("utf8")) {
				printf("Error loading character set utf8: %s\n", $conn->error);
				exit();
			}
			if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);
			} 
			if($_SERVER["REQUEST_METHOD"] == "POST"){
				
				$username = trim($_POST["username"]);
				$password = trim($_POST["password"]);
				
				// Validate username
				if(empty(trim($_POST["username"]))){
					$username_err = "Please enter a username.";
				}
				
				// Validate password
				if(empty(trim($_POST["password"]))){
					$password_err = "Please enter a password.";     
				}
				
				// Check input errors before inserting in database
				if(empty($username_err) && empty($password_err)){
					$sql = "select * from users where username = '".$username."';";
					$result = $conn->query($sql);
					$row = $result->fetch_assoc();
					if($result->num_rows != 0 && password_verify($password, $row["password"])){
						session_start();
						$_SESSION["login"] = true;
                        $_SESSION["username"] = $username;   
						echo "success!";
						header("location: home.php");						
					}
					else {
						$username_err = "wrong username or password";
						$password_err = "wrong username or password";     
					}
				}
				
			}
		?>
		
		<div class="wrapper">
			<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
				<div class="form-group <?php echo (!empty($username_err)) ? 'has-error' : ''; ?>">
					<label>Username</label>
					<input type="text" name="username" class="form-control" value="<?php echo $username; ?>">
					<span class="help-block"><?php echo $username_err; ?></span>
				</div>    
				<div class="form-group <?php echo (!empty($password_err)) ? 'has-error' : ''; ?>">
					<label>Password</label>
					<input type="password" name="password" class="form-control">
					<span class="help-block"><?php echo $password_err; ?></span>
				</div>
				<div class="form-group">
					<input type="submit" class="btn btn-primary" value="Login">
				</div>
				<p>Don't have an account? <a href="register.php">Register</a></p>
			</form>
		</div>    
	</div>
	
</body>
</html>
