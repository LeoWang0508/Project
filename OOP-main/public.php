<?php
	//頁首
	function loadPublic($n) {
		echo "
		<!-- 可收納導航欄，用法參考https://www.w3schools.com/bootstrap4/bootstrap_navbar.asp -->
		<nav class='navbar navbar-expand-md bg-dark navbar-dark'>
      <a class='navbar-brand justify-content-center' href='./Home.php' id='home'>Home</a>
        
        <button class='navbar-toggler' type='button' data-toggle='collapse' data-target='#navbarNavCollapse'>
          <span class='navbar-toggler-icon'></span>
        </button>

        <div class='collapse navbar-collapse' id='navbarNavCollapse'>
          
            <ul class='navbar-nav mr-auto'>";
			
			if($n==1){
              	echo "<li class='nav-item'><a  href='./Lobby.php' id='lobby' class='nav-link active'>Lobby</a></li>";
			}else{
				echo "<li class='nav-item'><a  href='./Lobby.php' id='lobby' class='nav-link'>Lobby</a></li>";
			}
			if($n==2){
				echo "<li class='nav-item'><a  href='./Forum.php' id='forum' class='nav-link active'>Forum</a></li>";
			}else{
				echo "<li class='nav-item'><a  href='./Forum.php' id='forum' class='nav-link'>Forum</a></li>";
			}
			if($n==3){
              	echo "<li class='nav-item'><a  href='./History.php' id='history' class='nav-link  active'>Histroy</a></li>";
			}else{
				echo "<li class='nav-item'><a  href='./History.php' id='history' class='nav-link'>Histroy</a></li>";
			}

            echo "</ul>";

			session_start();
            if(isset($_SESSION["login"]) && $_SESSION["login"]==true){
				echo "
				<form class='form-inline' action='./logout.php' id='logout' method='post'>
				<button type='submit' class='btn btn-warning mt-2'>LogOut</button>
				</form>";
			}else{
				echo "<form class='form-inline' action='./login.php' method='post'>    <!-- 後端登入操作放在這 -->";
				if(isset($_SESSION["username_err"]) && $_SESSION["username_err"]!=false){
					echo "<input type='text' class='form-control mt-2 mr-2' id='uname' placeholder='".$_SESSION["username_err"]."' name='uname'></input>";
				}else{
					echo "<input type='text' class='form-control mt-2 mr-2' id='uname' placeholder='Enter username' name='uname'></input>";
				}
				if(isset($_SESSION["password_err"]) && $_SESSION["password_err"]!=false){
					echo "<input type='password' class='form-control mt-2 mr-2' id='pwd' placeholder='".$_SESSION["password_err"]."' name='pswd'></input>";
				}else{
					echo "<input type='password' class='form-control mt-2 mr-2' id='pwd' placeholder='Enter password' name='pswd'></input>";
				}
				echo "<button type='submit' class='btn btn-warning mt-2 mr-2' id='login'>LogIn</button>
				</form>";
				$_SESSION["username_err"] = false;
				$_SESSION["password_err"] = false;

				echo "<form class='form-inline'>";
				echo "<button class='btn btn-warning mt-2' type='button' data-toggle='modal' data-target='#registerModal' >Register</button>";
				echo "</form>";

				echo "<div class='modal fade' id='registerModal'>
					<div class='modal-dialog'>
					<div class='modal-content'>
				
						<!-- Modal Header -->
						<div class='modal-header'>
						<h4 class='modal-title'>Register</h4>
						<button type='button' class='close' data-dismiss='modal'>&times;</button>
						</div>";
				echo "<div class='modal-body'>
					<form action='./register.php' id='register' method='post'>    <!-- 後端操作放在這 -->

						<p>User Name</p>
						<input type='text' class='form-control mb-3' name='uname'></input>

						<p>Password</p>
						<input type='password' class='form-control mb-3' name='password'></input>

						<p>Confirm Password</p>
						<input type='password' class='form-control mb-3' name='confirm_password'></input>

						<button type='submit' class='btn btn-primary'>Submit</button>
					</form>
					</div>";
				echo "<div class='modal-footer'>
					<button type='button' class='btn btn-danger' data-dismiss='modal'>Close</button>
					</div>";
			}
		echo "<script src=./HomeController.js></script>";
		echo "<script src=./LoginController.js></script>";
		echo "</div>

    </nav>";
	}

	//頁尾
	function loadFooter(){
		echo "<div class='container-sm' style='height: 50px;'></div>";
		echo "<div class='jumbotron jumbotron-fluid' style='height: 150px;margin-bottom: 0px;'>
		<div class='container' style='text-align: center;'>
		  <h1>台師大OOAD小組製作</h1>      
		</div>";
		echo "<!-- Bootstrap  -->
		<script src='https://code.jquery.com/jquery-3.5.1.slim.min.js' integrity='sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj' crossorigin='anonymous'></script>
		<script src='https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js' integrity='sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN' crossorigin='anonymous'></script>
		<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js' integrity='sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF' crossorigin='anonymous'></script>";
	}
?>