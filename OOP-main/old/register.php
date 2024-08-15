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
	<title>Register</title>
	<link rel='stylesheet' type='text/css' href='./style/public.css'>
</head>
<body>

	<?php loadPublic(); ?>

	<div class="title">
		<h1 align="center">Register</h1>
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
				$confirm_password = trim($_POST["confirm_password"]);
				
				// Validate username
				if(empty(trim($_POST["username"]))){
					$username_err = "Please enter a username.";
				} else{
					// Prepare a select statement
					$sql = "SELECT id FROM users WHERE username = '".$username."';";
					$result = $conn->query($sql);
					if($result->num_rows > 0){
						$username_err = "This username is already taken.";
					}
				}
				
				// Validate password
				if(empty(trim($_POST["password"]))){
					$password_err = "Please enter a password.";     
				} elseif(strlen(trim($_POST["password"])) < 6){
					$password_err = "Password must have atleast 6 characters.";
				}
				
				// Validate confirm password
				if(empty(trim($_POST["confirm_password"]))){
					$confirm_password_err = "Please confirm password.";     
				} else{
					if(empty($password_err) && ($password != $confirm_password)){
						$confirm_password_err = "Password did not match.";
					}
				}
				
				// Check input errors before inserting in database
				if(empty($username_err) && empty($password_err) && empty($confirm_password_err)){
					$hash_password = password_hash($password, PASSWORD_DEFAULT);
					$sql = "INSERT INTO users (user_id, username, password) VALUES (NULL,'".$username."','".$hash_password."');";
					$conn->query($sql);
					echo "Success!";
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
					<input type="password" name="password" class="form-control" value="<?php echo $password; ?>">
					<span class="help-block"><?php echo $password_err; ?></span>
				</div>
				<div class="form-group <?php echo (!empty($confirm_password_err)) ? 'has-error' : ''; ?>">
					<label>Confirm Password</label>
					<input type="password" name="confirm_password" class="form-control" value="<?php echo $confirm_password; ?>">
					<span class="help-block"><?php echo $confirm_password_err; ?></span>
				</div>
				<div class="form-group">
					<input type="submit" class="btn btn-primary" value="Submit">
					<input type="reset" class="btn btn-default" value="Reset">
				</div>
				<p>Already have an account? <a href="login.php">Login here</a>.</p>
			</form>
		</div>    
	</div>
	
</body>
</html>
