<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">

    <title>Lobby</title>

    <style>

      .container_height{
        position: relative;
        height: 550px;
      }

      .footer-height{
        height: 150px;
        margin-bottom: 0px;
      }
      
    </style>
  </head>
  <body>

    <?php
      include "public.php";
      loadPublic(1);
      session_start();
      /*
      $_SESSION["rooms"] = array();
      $_SESSION["clearRooms"] = array();
      */
      if(!isset($_SESSION["rooms"])){
        $_SESSION["rooms"] = array();
      }
      if(!isset($_SESSION["clearRooms"])){
        $_SESSION["clearRooms"] = array();
      }
    ?>

    <!-- 自訂義模組工具，用法參考https://www.w3schools.com/bootstrap4/bootstrap_modal.asp   -->
    <div class="container-sm pt-3">
          <?php
            if($_SESSION["login"]){
              echo "
              <form class='form-inline justify-content-center'>
                <!-- Button to Open the Modal1 -->
                <button class='btn btn-primary mr-2' type='button' data-toggle='modal' data-target='#myModal' >New</button>
                <a href='game.php' class='btn btn-primary mr-2' role='button'>Qucik Start</a>
                <!-- Button to Open the Modal2 -->
                <button type='button' class='btn btn-primary' data-toggle='modal' data-target='#myModal2'>Join</button>
              </form>
              ";
            }else{
              echo "<h2>Please Login</h2>";
            }
          ?>
          

    </div>  


    <!-- The NewGame Modal -->
    <div class="modal fade" id="myModal">
      <div class="modal-dialog">
        <div class="modal-content">
    
          <!-- Modal Header -->
          <div class="modal-header">
            <h4 class="modal-title">Creat a new game</h4>
            <button type="button" class="close" data-dismiss="modal">&times;</button>
          </div>
          
          <!-- Modal body -->
          <div class="modal-body">
            <form action="/changeRoomController.php" method="post">    <!-- 後端操作放在這 -->

              <p>Game</p>
              <select name="games" class="custom-select mb-3">  
                <option value="GoBang">GoBang</option>
                <option value="Connect6">Connect6</option>
              </select>

              <p>Board Size</p>
              <select name="Board_Size" class="custom-select mb-3">
                <option value="8x8">8x8</option>
                <option value="16x16">16x16</option>
              </select>

              <p>AI Allowed</p>
              <select name="AI_Allowed" class="custom-select mb-3">
                <option value="AI_True">True</option>
                <option value="AI_False">False</option>
              </select>

              <p>Time Limited</p>
              <select name="Time_Limited" class="custom-select mb-3">
                <option value="1min">1min</option>
                <option value="3min">3min</option>
                <option value="5min">5min</option>
              </select>

              <p>Regret</p>
              <select name="Regret" class="custom-select mb-3">
                <option value="Regret_True">True</option>
                <option value="Regret_False">False</option>
              </select>                


              <button type="submit" class="btn btn-primary" id="changeRoom">Submit</button>
            </form>
          </div>
      
          <!-- Modal footer -->
          <div class="modal-footer">
            <button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
          </div>
      
        </div>
      </div>
    </div>
    
    <!-- The JoinGame Modal -->
    <div class="modal fade" id="myModal2">
      <div class="modal-dialog">
        <div class="modal-content">
        
          <!-- Modal Header -->
          <div class="modal-header">
            <h4 class="modal-title">Join the game</h4>
            <button type="button" class="close" data-dismiss="modal">&times;</button>
          </div>
          
          <!-- Modal body -->
          <div class="modal-body">
            <form action="/action_page.php">    <!-- 後端操作放在這 -->
              <input class="form control mr-2" placeholder="Enter room number" id="room_num" name="room_num"></input>
              <br>
              <button type="submit" class="btn btn-primary mt-2">Submit</button>
            </form>
          </div>
          
          <!-- Modal footer -->
          <div class="modal-footer">
            <button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
          </div>
          
        </div>
      </div>
    </div>


    <div class="container pt-3 container_body_size" style="height:500px">
      <table class="table table-hover">
        <thead>
          <tr class='table-active'>
            <td>Room ID</td>
            <td>Game</td>
            <td>Player</td>
            <td>Board Size</td>
            <td>AI Allowed</td>
            <td>Time Limited</td>
            <td>Regret</td>
          </tr>
        </thead>
        <tbody>
          <?php
          for($i=0;$i<round(count($_SESSION["rooms"])/7);$i+=1){
            $ok = 1;
            for($j=0;$j<count($_SESSION["clearRooms"]);$j+=1){
              if($i===$_SESSION["clearRooms"][$j]){
                $ok = 0;
                break;
              }
            }
            if($ok===1){
              echo "<tr class='table-active'>";
              for($j=0;$j<7;$j+=1){
                if($j===0){
                  $h = "http://140.122.184.75:4000/".$_SESSION["rooms"][$i*7]."/2/".$_SESSION["rooms"][$i*7+2]."-".$_SESSION['username']."";
                  echo "<td><a href=".$h.">".$_SESSION["rooms"][$i*7+$j]."</a></td>";
                }else{
                  echo "<td>".$_SESSION["rooms"][$i*7+$j]."</td>";
                }
              }
              echo "</tr>";
            }
            

            $row = $result->fetch_assoc();
          }

          ?>
        </tbody>
      </table>

    </div>

  
  <div class="jumbotron jumbotron-fluid footer-height">
    <div class="container" style="text-align: center;">
      <h1>台師大OOAD小組製作</h1>      
    </div>
  </div>


  <!-- Bootstrap  -->
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js" integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js" integrity="sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF" crossorigin="anonymous"></script>


  </body>
</html>
