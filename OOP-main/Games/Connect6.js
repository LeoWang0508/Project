import Game from './Game.js';

export default class Connect extends Game{
    constructor (x_board_size, y_board_size){
        super();
        this.board_size = x_board_size * y_board_size;
        this.x_board_size = x_board_size;
        this.y_board_size = y_board_size;
    }


    /*判斷move是否合法 */
    check_valid_move(x, y, board){
        if (board[y][x] != 0){
            return false;
        }
        return true;
    }


    // 判斷遊戲是否結束 return winner
    get_game_ended(board){
        let winner = 0;
        //橫列有6子相連
        for (let i = 0; i < this.y_board_size; i++){
            for (let j = 0; j < 14; j++){
                    if( board[i][j] == 1 &&
                        board[i][j + 1] == 1 &&
                        board[i][j + 2] == 1 &&
                        board[i][j + 3] == 1 &&
                        board[i][j + 4] == 1 &&
                        board[i][j + 5] == 1){
                        
                        winner = 1;
                        return winner;
                    }

                    else if (board[i][j] == -1 &&
                        board[i][j + 1] == -1 &&
                        board[i][j + 2] == -1 &&
                        board[i][j + 3] == -1 &&
                        board[i][j + 4] == -1 &&
                        board[i][j + 5] == -1){
                        
                        winner = -1;
                        return winner;
                    }
            }
                
        }
        

        //直行有6子相連
        for (let j = 0; j < this.x_board_size; j++){
            for (let i =0; i < 14; i++){
                if (board[i][j] == 1 &&
                    board[i + 1][j] == 1 &&
                    board[i + 2][j] == 1 &&
                    board[i + 3][j] == 1 &&
                    board[i + 4][j] == 1 &&
                    board[i + 5][j] == 1){

                    winner = 1;
                    return winner;
                    }
                
                else if (board[i][j] == -1 &&
                    board[i + 1][j] == -1 &&
                    board[i + 2][j] == -1 &&
                    board[i + 3][j] == -1 &&
                    board[i + 4][j] == -1 &&
                    board[i + 5][j] == -1){

                    winner = -1;
                    return winner;
                    }
            }
        }

        //反斜線有6子相連
        for (let i = 0; i < 14; i++){
            for(let j = 0; j < 14; j++){
                if (board[i][j] == 1 &&
                    board[i + 1][j + 1] == 1 &&
                    board[i + 2][j + 2] == 1 &&
                    board[i + 3][j + 3] == 1 &&
                    board[i + 4][j + 4] == 1 &&
                    board[i + 5][j + 5] == 1){

                    winner = 1;
                    return winner;
                }
                else if (board[i][j] == 1 &&
                    board[i + 1][j + 1] == -1 &&
                    board[i + 2][j + 2] == -1 &&
                    board[i + 3][j + 3] == -1 &&
                    board[i + 4][j + 4] == -1 &&
                    board[i + 5][j + 5] == -1){

                    winner = -1;
                    return winner;
                }
            }
        }

        //正斜線有6子相連
        for (let i = 0; i < 14; i++){
            for (let j = 0; j < 14; j++){
                if (board[i + 5][j] == 1 &&
                    board[i + 4][j + 1] == 1 &&
                    board[i + 3][j + 2] == 1 &&
                    board[i + 2][j + 3] == 1 &&
                    board[i + 1][j + 4] == 1 &&
                    board[i][j + 5] == 1){
                    
                    winner = 1;
                    return winner;
                }
                else if (board[i + 5][j] == -1 &&
                    board[i + 4][j + 1] == -1 &&
                    board[i + 3][j + 2] == -1 &&
                    board[i + 2][j + 3] == -1 &&
                    board[i + 1][j + 4] == -1 &&
                    board[i][j + 5] == 1){

                    winner = -1;
                    return winner;
                    }
            }
        }
        return winner

    }

    // get_board_size(board){
    //     let x_board_size = board[0].length;
    //     let y_board_size = board.length;
    //     return [x_board_size, y_board_size]
    // }

    get_init_board(){

    }

    get_action_size(board){
        let action_size = [];
        for (let i = 0; i < this.x_board_size; i++){
            for (let j = 0; j < this.y_board_size; j++){

                if (board[i][j] == 0){
                    action_size.push([i, j]);
                }
            }
        }
        return action_size;
    }



    /*return which player's turn*/

    // player_to_play(){
    //     if (this.playerTurn == 1) {
    //         this.playerTurn = -1;
    //     }
    //     else if (this.playerTurn == -1) {
    //         this.playerTurn = -1;
    //     }
    // }


    // change_player_turn(){
    //     if (this.playerTurn == 1){
    //         this.playerTurn = -1;
    //     }
    //     else{
    //         this.playerTurn = 1;
    //     }
    // }

}


