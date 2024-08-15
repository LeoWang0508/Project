<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="description" content="">
        <title>testing Game</title>
    </head>
    <body>
        <canvas id="connect6" width="380px" height="380px"></canvas>
        <script type="module">
            import Connect6 from './Connect6.js';
            import GoBoard from './GoBoard.js';
            import GameFactory from './GameFactory.js';

            var splited = location.href.split('=')
            let gameID = splited[splited.length - 1];

            let goBoard = new GoBoard();
            let connect6 = new Connect6(19, 19);
            let gamefactory = new GameFactory(connect6, gameID, goBoard);
        </script>
        <?php
            $data = array("num" =>10);
            echo json_encode($data);
        ?>
    </body>
    
</html>