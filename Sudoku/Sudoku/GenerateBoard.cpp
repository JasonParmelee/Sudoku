#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "LinkedList.h"
#include "GenerateBoard.h"


int board[9][9];
int playBoard[9][9];

GenerateBoard::GenerateBoard()
{
	//sets the random seed to time so it is always more random
	std::srand(std::time(NULL));

	genBoard(board);
	genPlayBoard(board, playBoard);
	printBoard(board);
	std::cout << std::endl;
	printBoard(playBoard);
}

void GenerateBoard::genBoard(int board[9][9])
{
	//linked list of numbers between 1 and 9 for the board section to select from.
	//A linked list is used to dynamically remove the numbers invalid from the list
	LinkedList * availableNum = new LinkedList();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			refillList(availableNum);
			genNum(9, i, j, availableNum, board);
		}
	}

	//Check if the board is filled, if not, the combination is not valid and must be regenerated
	if (checkBoard(board))
	{
		//reset the board
		resetBoard(board);
		//recall genBoard
		genBoard(board);
	}

	return;
}

void GenerateBoard::genNum(int num, int i, int j, LinkedList * list, int board[9][9])
{
	//Base Case, if num has reached 0, we can go no further, so return
	if (num < 1)
	{
		return;
	}

	//Pick a random number between 0 and num (which starts at 9)
	//This number will serve as the location of the list from which to grab a number
	int randNum = rand() % num;

	//Horizontal Check
	if (!isIn(list->get(randNum), board[i]))
	{
		//Vertical Vertical Check
		if (!isIn(list->get(randNum), j, board))
		{
			//3x3 grid Check
			if (!isIn(list->get(randNum), i, j, board))
			{
				//if it is NOT in any of the checks, the number can be added to the board, and return
				board[i][j] = list->get(randNum);
				return;
			}
			else
			{
				list->deleteNum(randNum);
				genNum(num - 1, i, j, list, board);
			}
		}
		else
		{
			list->deleteNum(randNum);
			genNum(num - 1, i, j, list, board);
		}
	}
	else
	{
		//For all three else cases, the number is deleted from the available numbers list, and the function is called again from num - 1 and the reduced list
		list->deleteNum(randNum);
		genNum(num - 1, i, j, list, board);
	}
	
	return;
}

void GenerateBoard::genPlayBoard(int board[9][9], int playBoard[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (i)
			{
			case 0:
				//Generates empty spots for the top line of the board
				if (j == 0 || j == 2 || j == 4 || j == 5 || j == 6 || j == 7 || j == 8)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 1:
				//Generates empty spots for line i = 1
				if (j == 0 || j == 1 || j == 4 || j == 7)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 2:
				//Generates empty spots for line i = 2
				if (j == 0 || j == 1 || j == 3 || j == 5 || j == 6)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 3:
				//Generates empty spots for line i = 3
				if (j == 1 || j == 2 || j == 3 || j == 5)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 4:
				if (j == 0 || j == 1 || j == 2 || j == 6 || j == 7 || j == 8)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 5:
				if (j == 3 || j == 5 || j == 6 || j == 7)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 6:
				if (j == 2 || j == 3 || j == 5 || j == 7 || j == 8)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 7:
				if (j == 1 || j == 4 || j == 7 || j == 8)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			case 8:
				if (j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 6 || j == 8)
				{
					playBoard[i][j] = 0;
					continue;
				}
				else
					playBoard[i][j] = board[i][j];
				break;
			default:
				break;
			}
		}
	}

	return;
}

//This function clears the linked list of available number and refills it. 
void GenerateBoard::refillList(LinkedList * list)
{
	//For the list size, delete the number in the first position, to empty the list
	for (int i = 0; i < (*list).size(); i++)
	{
		(*list).deleteNum(0);
	}
	//Then, refill the list with 1-9
	for (int i = 0; i < 9; i++)
	{
		(*list).add(i + 1);
	}
}

//Overload 1: this checks the horizontal row of the board for matching nums
bool GenerateBoard::isIn(int num, int arrayNum[9])
{
	for (int i = 0; i < 9; i++)
	{
		if (num == arrayNum[i])
		{
			return true;
		}
	}

	return false;
}

//Overload 2: this checks the vertical row of the board for matching nums
bool GenerateBoard::isIn(int num, int j, int arrayNum[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		if (num == arrayNum[i][j])
		{
			return true;
		}
	}

	return false;
}

//Overload 3: this checks the 3x3 array of nums in Sudoku for matching nums
bool GenerateBoard::isIn(int num, int i, int j, int arrayNum[9][9])
{
	//Always 0, 3, or 6 (0->2 is 0, 3->5 is 3, 6->8 is 6)
	int newI = ((i / 3) * 3);
	int newJ = ((j / 3) * 3);

	//Always 3, 6, or 9 (0->2 is 3, 3->5 is 6, 6->8 is 9)
	int newI2 = (((i / 3)+1) * 3);
	int newJ2 = (((j / 3)+1) * 3);

	for (int k = newI; k < newI2; k++)
	{
		for (int l = newJ; l < newJ2; l++)
		{
			//We don't want to check the current position, so skip
			if (k == i && l == j)
			{
				continue;
			}

			if (num == arrayNum[k][l])
			{
				return true;
			}
		}
	}

	return false;
}

//Checks the board to see if any position has not been filled (meaning it remained 0 after genBoard)
//if true, it means to current arrangement of numbers is not a valid Sudoku board and must be regenerated
bool GenerateBoard::checkBoard(int board[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

//Resets each position in the board array to 0
void GenerateBoard::resetBoard(int board[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = 0;
		}
	}

	return;
}

//Prints the board, as well as seperators for each 3x3 array
void GenerateBoard::printBoard(int board[9][9])
{
	for (int i = 0; i < 11; i++)
	{
		if (i == 3 || i == 7)
		{
			std::cout << "----------------------";
		}
		else
		{
			for (int j = 0; j < 9; j++)
			{
				if (j == 2 || j == 5)
				{
					if (i >= 3 && i < 7)
					{
						if (board[i - 1][j] == 0)
							std::cout << "_ | ";
						else
							std::cout << board[i - 1][j] << " | ";
					}
					else if (i >= 7)
					{
						if (board[i - 2][j] == 0)
							std::cout << "_ | ";
						else
							std::cout << board[i - 2][j] << " | ";
					}
					else
					{
						if (board[i][j] == 0)
							std::cout << "_ | ";
						else
							std::cout << board[i][j] << " | ";
					}
				}
				else
				{
					if (i >= 3 && i < 7)
					{
						if (board[i - 1][j] == 0)
							std::cout << "_ ";
						else
							std::cout << board[i - 1][j] << " ";
					}
					else if (i >= 7)
					{
						if (board[i - 2][j] == 0)
							std::cout << "_ ";
						else
							std::cout << board[i - 2][j] << " ";
					}
					else
					{
						if (board[i][j] == 0)
							std::cout << "_ ";
						else
							std::cout << board[i][j] << " ";
					}
				}
			}
		}

		std::cout << std::endl;
	}
}

GenerateBoard::~GenerateBoard()
{
}
