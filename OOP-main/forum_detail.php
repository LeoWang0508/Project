<?php
	include "public.php";
	$servername = "localhost";
	$dbusername = "ooproject";
	$dbpassword = "ooproject";
	$dbname = "oop";
    session_start();
    $id = (int)$_GET[id];
    $_SESSION["forum_id"] = $id;
?>

<!doctype html>
<html lang="en">
  <head>
    
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
    <title>Forum_detail</title>

  </head>
  <body>

    <?php
        loadPublic(2);
    ?>

    <div class="container-sm pt-3 container_body_size">
        <?php
            $conn = new mysqli($servername, $dbusername, $dbpassword, $dbname);
            $sql = "select * from forum where forum_id='".$id."';";
            $result = $conn->query($sql);
            $row = $result->fetch_assoc();
        ?>

        <table class="table table-striped">
            <thead>
                <?php
                    echo "<tr class='table-secondary'>";
                    echo "<td>Tital:".$row["tital"]."</td>";
                    echo "<td>Game:".$row["game_name"]."</td>";
                    echo "</tr>";
                    echo "<tr class='table-dark text-dark'>";
                    echo "<td>User:".$row["user"]."</td>";
                    echo "<td>Time:".$row["time"]."</td>";
                    echo "</tr>";
                    echo "<tr>";
                    echo "<td colspan='2'>".$row["detail"]."</td>";
                    echo "</tr>";
                ?>
            </thead>
            <?php
                $sql = "select * from forum where parent_id='".$id."';";
                $result = $conn->query($sql);
                $row = $result->fetch_assoc();
            ?>
            <tbody>
                <?php
                    while($row) {
                        echo "<tr class='table-dark text-dark'>";
                        echo "<td>User:".$row["user"]."</td>";
                        echo "<td>Time:".$row["time"]."</td>";
                        echo "</tr>";
                        echo "<tr>";
                        echo "<td colspan='2'>".$row["detail"]."</td>";
                        echo "</tr>";

                        $row = $result->fetch_assoc();
                    }

                ?>
            </tbody>
        </table>
        
        <?php
            session_start();
            if($_SESSION["login"]==true){
                echo "<form action='./post.php' method='post'>
                    <div class='form-group'>
                    <label for='comment'>Comment:</label>
                    <textarea class='form-control' rows='5' placeholder='Must contain at least 6 characters' id='comment' name='detail'></textarea>
                    </div>
                    <button type='submit' class='btn btn-primary'>Submit</button>
                    </form>";
            }
        ?>

    </div>

    <script src=./ForumController.js></script>
    <?php
        loadFooter();
    ?>

  </body>
</html>