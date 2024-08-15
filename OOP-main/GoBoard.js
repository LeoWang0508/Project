import Board from './Board.js'

export default class GoBoard extends Board{
    constructor(){
        super();
        this.x_board_size = this.get_board_size()[0];
        this.y_board_size = this.get_board_size()[1];
        this.board = this.init_board(this.x_board_size, this.y_board_size);
        
    }

    get_board(){
        return this.board;
    }

    get_board_size(){
        let x_board_size = 19;
        let y_board_size = 19;
        return [x_board_size, y_board_size];
    }

    draw_board(){
        let board_canvas = document.getElementById("connect6");
        board_canvas.style.backgroundColor = "#CD853F";

        let context = board_canvas.getContext("2d");
        context.strokeStyle = "#000000";
        
        //draw board lines
        for (let i = 0; i < 19; i++){

            context.moveTo(10, 10 + 20 * i);
            context.lineTo(370, 10 + 20 * i);
            context.stroke();

            context.moveTo(10 + 20 * i, 10);
            context.lineTo(10 + 20 * i, 370);
            context.stroke();
        }
    
        return board_canvas;
    }
    // board_canvas : 畫棋盤的畫布, player : 輪到下棋的玩家, 1為先手 0為後手
    draw_chess(x, y, board_canvas, player){
        let context = board_canvas.getContext("2d");

        //one step 畫棋子
        let color;
        context.beginPath();
        context.arc(10 + 20 * x, 10 + 20 * y, 9, 0, 2 * Math.PI);
        context.closePath();

        if (player == 1){
            color = "black";
            player = -1;
        }
        else{
            color = "white";
            player == 1;
        }

        context.fillStyle = color;
        context.fill();

    }
    update_board_state(x, y, playerTurn){
        this.board[y][x] = playerTurn;
        // console.log(this.board);
    }

    // init_board(x_board_size, y_board_size){
    //     let board = new Array(y_board_size);
    //     // console.log(board);
    //     for (let i = 0; i < y_board_size; i++){
    //         board[i] = new Array(x_board_size);
    //         board[i].fill(0);
    //     }
    //     // console.log(board);
    //     return board
    // }

}

