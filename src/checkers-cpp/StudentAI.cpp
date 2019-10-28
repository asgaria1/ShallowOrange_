#include "StudentAI.h"
#include <random>
int COUNT = 0;
//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col,int row,int p)
        :AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move)
{
    int curr = -100;
    Move bestMove;
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    COUNT++;
    vector<vector<Move> > moves = board.getAllPossibleMoves(player);
    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves[i].size(); j++){
            //make move on board so u can pass it to minimax function
            board.makeMove(moves[i][j], player);
            int result = basic_minimax(board, player, 3, "min"); //will return a number for this move, the higher the better
            if (result > curr) {
                curr = result;
                bestMove = moves[i][j];
            }
            board.Undo(); //undo change in order to test another move
        }
    }
    cout<<"done finding moves: "<<bestMove.toString()<<endl;
    board.makeMove(bestMove, player);
    return bestMove;
}

int StudentAI::getScore(Board board, int player)
{
    int myCount = 0;
    int oppCount = 0;
    string me = player == 1? "B":"W";
    string opp = me =="B"? "W":"B";
    for (int row = 0; row < board.board.size(); row++){
        for (int col = 0; col < board.board[row].size(); col++){
            if (board.board[row][col].color == me){
                myCount++;
            }
            else if (board.board[row][col].color == opp){
                oppCount++;
            }
        }
    }
    return myCount - oppCount;
}

int StudentAI::basic_minimax(Board board, int player, int depth, string state){
    //the board object do not know whose turn it is, its makeMove simply takes a player argument and act the move
    //for that player. The turn order is maintained by GameLogic.
    //Therefore, in order to make the move for the right player on each recursive level, we need to check whether if
    //its min or max's turn. since for this function, player is initial player that started this function. If state is
    //max then the current player taking the turn is the same as player, else it is the opponent.. Another way to do this
    //is to change it to the right player when doing the recursive call, this way we just have to check when we do the final
    //evaluation...
    if (depth == 0) {

        return getScore(board, player);
    }
    int thisTurnPlayer;
    int curBestValue;//keeping track of the best val of move I can make, if im a min then the lower the better, if im
    //a max then higher the better

    if (state=="max"){
        thisTurnPlayer = player; //since state is max then the player moving this turn is the same as the init player
        curBestValue = -100;
    }
    else{
        thisTurnPlayer = player == 1? 2:1; //reverse if state is min
        curBestValue = 100;
    }

    vector<vector<Move> > moves = board.getAllPossibleMoves(thisTurnPlayer); //get the moves for the player moving this turn

    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves[i].size(); j++){
            //make move on board so u can pass it to minimax function


            board.makeMove(moves[i][j], thisTurnPlayer);
            string nextState = state == "min"? "max":"min";
            int result = basic_minimax(board, player, depth -1, nextState); //will return a number for this move, the higher the better
            //passed depth -1 for recursive base case + passed next state instead of state because u want to
            //recursively call the next state, not the current state
            if ( state == "min" ){
                if (result < curBestValue) {
                    curBestValue = result;
                }
            }else { // state == "max"
                if (result > curBestValue) {
                    curBestValue = result;
                }
            }

            board.Undo(); //undo change in order to test another move
        }
    }
    return curBestValue;
}