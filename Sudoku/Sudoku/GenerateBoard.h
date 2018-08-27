#pragma once
#include "LinkedList.h"
class GenerateBoard
{
public:
	GenerateBoard();
	~GenerateBoard();

private:
	void genBoard(int board[9][9]);
	void genNum(int num, int i, int j, LinkedList * list, int board[9][9]);
	void genPlayBoard(int board[9][9], int playBoard[9][9]);
	void refillList(LinkedList * list);
	bool isIn(int num, int arrayNum[9]);
	bool isIn(int num, int j, int arrayNum[9][9]);
	bool isIn(int num, int i, int j, int arrayNum[9][9]);
	bool checkBoard(int board[9][9]);
	void resetBoard(int board[9][9]);
	void printBoard(int board[9][9]);
};

