<?php
  $servername = "localhost";
  $dbusername = "ooproject";
  $dbpassword = "ooproject";
  $dbname = "oop";

  $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">

    <title>Forum</title>

  </head>
  <body>

    <?php
      include "public.php";
      loadPublic(2);
      session_start();
    ?>

    <div class="container-sm pt-3">
      <form class="form-inline justify-content-center" action="get_forum.php" method="post">
          <!-- Button to Open the Modal -->
          <div class='mr-2'><a>Games:</a></div>
          <select name="game_name" class="custom-select mr-2" method='post'> 
            <option value="All">All</option>
            <option value="GoBang">GoBang</option>
            <option value="Connect6">Connect6</option>
          </select>
          <button type="submit" class="btn btn-primary mr-2" id="get_forum">Submit</button>
          <?php
            if($_SESSION["login"]==true){
              echo "<button class='btn btn-primary' type='button' data-toggle='modal' data-target='#postModal' >New Post</button>";
            }
          ?>
        </form>
    </div>
  <div class="container pt-3 container_body_size" style="height:500px">
    <?php
      if(!isset($_SESSION["result"]) || $_SESSION["result"]==FALSE){
        header("location: get_forum.php");
      }
      $result = $conn->query($_SESSION["result"]);
      $row = $result->fetch_assoc();
    ?>

    <table class="table table-hover">
      <tbody>
        <?php
        while($row) {
          echo "<tr class='table-active'>";
          echo "<td>Tital:<a href='forum_detail.php?id=".$row["forum_id"]."' id='forum_detail'>".$row["tital"]."</a></td>";
          echo "<td>User:".$row["user"]."</td>";
          echo "</tr>";
          echo "<tr>";
          echo "<td>Game:".$row["game_name"]."</td>";
          echo "<td>Time:".$row["time"]."</td>";
          echo "</tr>";

          $row = $result->fetch_assoc();
        }

        ?>
      </tbody>
    </table>
        
  </div>

  <div class="modal fade" id="postModal">
    <div class="modal-dialog">
      <div class="modal-content">
      
        <!-- Modal Header -->
        <div class="modal-header">
          <h4 class="modal-title">New Post</h4>
          <button type="button" class="close" data-dismiss="modal">&times;</button>
        </div>
        
        <!-- Modal body -->
        <div class="modal-body">
          <form action="./post.php" method="post">    <!-- 後端操作放在這 -->
            <label for='tital'>Tital</label>
            <input class="form control mr-2" id='tital' name="tital"></input>
            <p>Game</p>
              <select name="game_name" class="custom-select mb-3">  
                <option value="All">All</option>
                <option value="GoBang">GoBang</option>
                <option value="Connect6">Connect6</option>
              </select>
            <div class='form-group'>
              <label for='comment'>Detail</label>
              <textarea class='form-control  mr-2' rows='6' placeholder='Must contain at least 6 characters' id='comment' name='detail'></textarea>
            </div>
            <br>
            <button type="submit" id='post' class="btn btn-primary mt-2">Submit</button>
          </form>
        </div>
        
        <!-- Modal footer -->
        <div class="modal-footer">
          <button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
        </div>
        
      </div>
    </div>
  </div>

  <script src=./ForumController.js></script>
  <?php
    loadFooter();
  ?>

  </body>
</html>