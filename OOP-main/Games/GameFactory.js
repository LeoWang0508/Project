export default class GameFactory {
    constructor(game, gameID, board){
        this.board = board;
        this.game = game;
        this.board_array;
        this.board_canvas;
        this.gameID = gameID;

        this.create_game();
        this.play_game();
    }


    //initialize game, create a new game
    create_game(){
        //get board array
        this.board_array = this.get_board_array();

        //draw board
        this.board_canvas = this.init_board(this.game, this.board);
    }


    //draw the board
    init_board(){
        return this.board.draw_board();
    }


    play_game(){
        
        this.click = function(e){

            let i = (e.offsetX / 20) | 0;
            let j = (e.offsetY / 20) | 0;
    
            let x = i;
            let y = j;
            

//             console.log(x, y);
            

            let winner = this.check_win(this.board_array);


            if (winner == 1){
                alert("player1 win");
            }
            else if (winner == -1){
                alert("player2 win");
            }

            if (this.game.check_valid_move(x, y, this.board_array) && winner == 0){
                this.update_board_state(x, y, this.game.player_to_play());
                this.oneStep(x, y);
                this.save_move(x, y);
            }
            else if (!this.game.check_valid_move(x, y, this.board_array)){
                alert("this is not a valid move, please move again");
            }

            
        }

        this.board_canvas.addEventListener("click", this.click.bind(this));
    }
    

    get_board_array(){
        return this.board.get_board();
    }


    oneStep(x, y){

        this.board.draw_chess(x, y, this.board_canvas, this.game.player_to_play());
        this.game.change_player_turn();

        if (this.check_win(this.board_array) != 0){
            alert("game finished");
        }
        
    }


    check_win(board){
        return this.game.get_game_ended(this.board_array);
    }


    update_board_state(x, y, playerTurn){
            this.board.update_board_state(x, y, playerTurn);
    }

    save_move(x, y){
        this.game.save_move(x, y);
    }

}
