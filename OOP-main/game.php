<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">

    <title>Game</title>

    <style>
    </style>
  </head>
  <body>

    <?php
      include "public.php";
      loadPublic();
    ?>

    <!-- 功能切換，用法參考https://www.w3schools.com/bootstrap4/bootstrap_ref_js_tab.asp -->
    <div class="container-sm">
        <div class="container-sm">
            <h2>Game Controller</h2>
            <p>Room :</p>
            <p>Player1 :</p>
            <p>Player2 :</p>
        </div>
        
        <!-- Nav tabs -->
        <ul class="nav nav-tabs">

          <li class="nav-item">
            <a class="nav-link active" data-toggle="tab" href="#home">Board</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" data-toggle="tab" href="#menu1">Chat</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" data-toggle="tab" href="#menu2">Record</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" data-toggle="tab" href="#menu3">Setting</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="Index.html">Exit</a>
          </li>

        </ul>
      
        <!-- Tab panes -->
        <div class="tab-content" style="height: 540px">

          <div id="home" class="container tab-pane active"><br>
            <p>Implement the game screen here.</p>
          </div>
          <div id="menu1" class="container tab-pane fade"><br>
            <p>Implement the chat room function here.</p>
          </div>
          <div id="menu2" class="container tab-pane fade"><br>
            <p>Implement the game record function here.</p>
          </div>
          <div id="menu3" class="container tab-pane fade"><br>
            <p>Implement the game setting function here.</p>
          </div>

        </div>
    </div>
    
    <!-- Bootstrap  -->
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js" integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js" integrity="sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF" crossorigin="anonymous"></script>


  </body>
</html>
