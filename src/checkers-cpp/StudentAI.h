#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);

	//=================================
	int getScore(Board board, int player); //get the heuristic score for the current board, which number of my pieces - number of my opponent's
    int basic_minimax(Board board, int player, int depth, string state); //basic minimax alg for determining move for studentAI

};

#endif //STUDENTAI_H
