<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";

    $id = (int)$_GET[id];
    $step = (int)$_GET[step];

    session_start();
    $user_name = $_SESSION["username"];

    $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
    if (!$conn->set_charset("utf8")) {
        printf("Error loading character set utf8: %s\n", $conn->error);
        exit();
    }
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
    $sql = "select * from history where game_id = '".$id."' && (player1='".$user_name."' || player2='".$user_name."');";
    $result = $conn->query($sql);
    $row = $result->fetch_assoc();
    if($row){
        $board_size = $row["board_size"];

        $sql = "select * from action where game_id = '".$id."' && step<='".$step."';";
        $result = $conn->query($sql);
        $num_rows = $result->num_rows;
        $row = $result->fetch_assoc();

        $action[$num_rows][2];

        $i = 0;
        while($row){
            $action[$i][0] = $row["step"];
            $action[$i][1] = $row["action"];
            $i += 1;
            $row = $result->fetch_assoc();
        }

        $width = 400;
        $side_width = 13;
        $img = imagecreatetruecolor($width, $width);		// create a 300*300 image
        $white = imagecolorallocate($img, 255, 255, 255);	// allocate color
        $black = imagecolorallocate($img, 0, 0, 0);
        $red   = imagecolorallocate($img, 255, 0, 0);	 
        $background = imagecolorallocate($img, 255, 145, 0);

        imagefill($img, 0, 0, $background);			// image background

        // board
        $x = 0; $dx = ($width-$side_width*2)/($board_size-1);
        for($x=1;$x<($board_size-1);$x++){
            imageline($img, $side_width+$dx*$x, $side_width, $side_width+$dx*$x, $width-$side_width-1, $black);
            imageline($img, $side_width, $side_width+$dx*$x, $width-$side_width-1, $side_width+$dx*$x, $black);
        }

        // 畫矩形(底圖, X1座標, Y1座標, X2座標, Y2座標, 顏色);
        imagerectangle($img, $side_width, $side_width, $width-1-$side_width, $width-1-$side_width, $black);		// 畫空心矩形

        // 畫圓(底圖, X座標, Y座標, width(寬), height(高),  起始度數, 結束度數, 空心圓顏色);
        $i = 0;$j = 0;
        for($i=-1;$i<2;$i++){
            for($j=-1;$j<2;$j++){
                imagefilledarc($img, $width/2-$i*6*$dx, $width/2-$j*6*$dx, $dx/3, $dx/3,  0, 360, $black, IMG_ARC_PIE);
            }
        }

        //落子
        for($i=0;$i<$num_rows;$i++){
            if($action[$i][0]%2==0){
                imagefilledarc($img, $side_width+$action[$i][1]%$board_size*$dx, $side_width+(int)($action[$i][1]/$board_size)*$dx, $dx, $dx,  0, 360, $black, IMG_ARC_PIE);
            }else{
                imagefilledarc($img, $side_width+$action[$i][1]%$board_size*$dx, $side_width+(int)($action[$i][1]/$board_size)*$dx, $dx, $dx,  0, 360, $white, IMG_ARC_PIE);
            }
        }
        imagefilledarc($img, $side_width+$action[$num_rows-1][1]%$board_size*$dx, $side_width+(int)($action[$num_rows-1][1]/$board_size)*$dx, $dx/3, $dx/3,  0, 360, $red, IMG_ARC_PIE);
        if($action[$num_rows-2][0]==$action[$num_rows-1][0]){
            imagefilledarc($img, $side_width+$action[$num_rows-2][1]%$board_size*$dx, $side_width+(int)($action[$num_rows-2][1]/$board_size)*$dx, $dx/3, $dx/3,  0, 360, $red, IMG_ARC_PIE);
        }
        // output image in the browser
        header("Content-type: image/png");
        imagepng($img);

        // free memory
        imagedestroy($img);
    }
?>