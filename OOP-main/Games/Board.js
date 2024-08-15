export default class Board{
    constructor(){

    }
    
    get_board(){
        
    }

    init_board(x_board_size, y_board_size){
        let board = new Array(y_board_size);

        for (let i = 0; i < y_board_size; i++){
            board[i] = new Array(x_board_size);
            board[i].fill(0);
        }

        return board;
    }

    draw_board(){

    }

    draw_chess(){
        
    }
}
