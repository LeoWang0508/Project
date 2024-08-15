export default class Game {
    constructor(){
        this.playerTurn = 1;
        this.history = [];
    }

    check_valid_move(board, player){

    }

    get_game_ended(board){

    }

    get_board_size(board){
        let x_board_size = board[0].length;
        let y_board_size = board.length;
        return [x_board_size, y_board_size];
    }

    get_init_board(){
    }

    get_action_size(){

    }

    //return which player's turn
    player_to_play(){
        return this.playerTurn;
    }

    change_player_turn(){
        if (this.playerTurn == 1){
            this.playerTurn = -1;
        }
        else{
            this.playerTurn = 1;
        }
    }

    save_move(x, y){
        this.history.push(x + y * 19);
    }

}