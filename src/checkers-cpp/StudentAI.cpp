#include "StudentAI.h"
#include <math.h>
#include <utility>
//



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
    int curr = -999;
    Move bestMove;
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }

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

            else if (result == curr){
                std::uniform_int_distribution<int> dist(0, 1);
                std::default_random_engine generator( rd() );

                int roll = dist(generator);
//                int roll = rand()%2;

                if (roll == 1){
                    curr = result;
                    bestMove = moves[i][j];
                }
            }
            board.Undo(); //undo change in order to test another move
        }
    }

    board.makeMove(bestMove, player);



    return bestMove;



}

int StudentAI::getScore(Board board, int player)
{
    bool endGame = true; //will set to false when a non-king is seen
    vector<pair<int, int>> myKings; //my kings
    vector<pair<int, int>> theirUnits; //their units
    int myCount = 0;
    int oppCount = 0;
    string me = player == 1? "B":"W";
    string opp = me =="B"? "W":"B";
    for (int row = 0; row < board.board.size(); row++){
        for (int col = 0; col < board.board[row].size(); col++){
            if (board.board[row][col].color == me){
                myCount++;
                if (board.board[row][col].isKing){
                    myKings.emplace_back(pair<int,int>(row, col));
                    myCount += 4;
                }
                else{
                    endGame = false;
                }
            }
            else if (board.board[row][col].color == opp){
                oppCount++;
                theirUnits.emplace_back(pair<int,int>(row, col));
                if (board.board[row][col].isKing){
                    oppCount += 4;
                }
                else{
                    endGame = false;
                }
            }
        }
    }
    int avgDist = 0;
    double sumAvgDist = 0; //sum of all average distance

    if (myKings.size() != 0 && theirUnits.size() != 0){
        for (int i = 0; i < myKings.size(); i++){
            double myTotal = 0;
            for (int j = 0; j < theirUnits.size(); j++){
                myTotal += getDistance(myKings[i], theirUnits[j]);
            }
            if (theirUnits.size() != 0){
                sumAvgDist += myTotal/theirUnits.size();
            }

        }

        int avgDist = floor(sumAvgDist / myKings.size());
        //cout<<"king avg distance:" << avgDist<<endl;

    }

    if (!endGame){return myCount - oppCount - (sumAvgDist);}

    if (myKings.size() >= theirUnits.size()){
        return sumAvgDist * -1;
    }
    return sumAvgDist;

}

int StudentAI::basic_minimax(Board board, int player, int depth, string state){
    //the board object do not know whose turn it is, its makeMove simply takes a player argument and act the move
    //for that player. The turn order is maintained by GameLogic.
    //Therefore, in order to make the move for the right player on each recursive level, we need to check whether if
    //its min or max's turn. since for this function, player is initial player that started this function. If state is
    //max then the current player taking the turn is the same as player, else it is the opponent.. Another way to do this
    //is to change it to the right player when doing the recursive call, this way we just have to check when we do the final
    //evaluation...
    //board.showBoard();

    if (depth == 0) {

        return getScore(board, player);
    }
    int thisTurnPlayer;
    int curBestValue;//keeping track of the best val of move I can make, if im a min then the lower the better, if im
    //a max then higher the better
    //Move bestMove; //keeping track of the actual best move to be made NO NEED

    if (state=="max"){
        thisTurnPlayer = player; //since state is max then the player moving this turn is the same as the init player
        curBestValue = -999;
    }
    else{
        thisTurnPlayer = player == 1? 2:1; //reverse if state is min
        curBestValue = 999;
    }

    vector<vector<Move> > moves = board.getAllPossibleMoves(thisTurnPlayer); //get the moves for the player moving this turn


    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves[i].size(); j++) {
            //make move on board so u can pass it to minimax function

            board.makeMove(moves[i][j], thisTurnPlayer);


            string nextState = state == "min"? "max":"min";
            int result = basic_minimax(board, player, depth -1, nextState); //will return a number for this move, the higher the better
            //passed depth -1 for recursive base case + passed next state instead of state because u want to
            //recursively call the next state, not the current state
            //=================================== kuixi break
            if ( state == "min" ){
                if (result < curBestValue) {
                    curBestValue = result;
                    //bestMove = moves[i][j];
                }
            }else { // state == "max"
                if (result > curBestValue) {
                    curBestValue = result;
                    //bestMove = moves[i][j];
                }
            }

            board.Undo(); //undo change in order to test another move

        }
    }
    return curBestValue;
}

double StudentAI::getDistance(pair<int, int> x, pair<int, int> y){

    int a = abs(x.first - y.first);
    int b = abs(x.second - y.second);


    return sqrt(a ^ 2 + b ^ 2);

}