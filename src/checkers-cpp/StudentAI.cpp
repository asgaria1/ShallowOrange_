#include "StudentAI.h"
#include <random>

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
    int curr = 0;
    Move bestMove;
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    vector<vector<Move> > moves = board.getAllPossibleMoves(player);
    for (int i = 0; i <= moves.size(); i++){
        for (int j = 0; j <= moves[i].size(); j++){
            //make move on copy of board so u can pass it min
            curr = basic_minimax(board, player, 4, "min");
        }
    }
    //int i = rand() % (moves.size());
    //vector<Move> checker_moves = moves[i];
    //int j = rand() % (checker_moves.size());
    //Move res = checker_moves[j];
    //board.makeMove(res,player);
    cout<<getScore(board)<<endl;
    return res;


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
    //int curr_score = getScore(board, player);
    //std::pair move_pair = std::pair(getScore(board, player), move??)

    if (depth == 0) {
        return getScore(board, player);
    }
    if max:
        get alll motsves
        cur best = stdpair(sdasd)
        for aeach nvoemoves
            make move on copy of board:
            let x = basic_miiamax(thisnewboard, player , deptht -1, max if this is min
            if x[0] > best[0] best = x
}