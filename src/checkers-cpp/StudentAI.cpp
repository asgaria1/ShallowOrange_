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

    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    vector<vector<Move> > moves = board.getAllPossibleMoves(player);
    int i = rand() % (moves.size());
    vector<Move> checker_moves = moves[i];
    int j = rand() % (checker_moves.size());
    Move res = checker_moves[j];
    board.makeMove(res,player);
    cout<<getScore(board)<<endl;
    return res;


}

int StudentAI::getScore(Board board)
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