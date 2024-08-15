<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">

    <title>Home</title>

    <style>

      .footer-height{
        height: 150px;
        margin-bottom: 0px;
      }

    </style>
  </head>
  <body>

    <?php
      include "public.php";
      loadPublic(0);
    ?>

    <!-- 展示牆，用法參考https://www.w3schools.com/bootstrap4/bootstrap_carousel.asp  -->
    <div class="container-sm pt-3" style="height: 550px">

      <div id="demo" class="carousel slide" data-ride="carousel">

        <!-- Indicators -->
        <ul class="carousel-indicators">
          <li data-target="#demo" data-slide-to="0" class="active"></li>
          <li data-target="#demo" data-slide-to="1"></li>
        </ul>
        
        <!-- The slideshow -->
        <div class="carousel-inner">
          <div class="carousel-item active">
            <img src="bimg1.jpg" width="100%" height="100%" >
          </div>
          <div class="carousel-item">
            <img src="bimg2.jpg" width="100%" height="100%" >
          </div>
        </div>
        
        <!-- Left and right controls -->
        <a class="carousel-control-prev" href="#demo" data-slide="prev">
          <span class="carousel-control-prev-icon"></span>
        </a>
        <a class="carousel-control-next" href="#demo" data-slide="next">
          <span class="carousel-control-next-icon"></span>
        </a>
        
      </div>

    </div>
    
    <?php
    loadFooter();
    ?>

  </body>
</html>
