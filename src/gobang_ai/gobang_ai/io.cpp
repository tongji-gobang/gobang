#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "board.h"

//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;

#define	ComPiece	'+'
#define HumPiece	'o'
#define EmpPiece	'-'

/*
	* 调试用，直接输出到 console
*/
int board::CommandPrint() const
{
	std::cout << "当前局面为:\n" << std::endl;
	std::cout << setfill('-') << setw(3 * BROAD_SIZE + 2) << std::endl;
	for ( int row = 0; row < BROAD_SIZE; ++row )
	{
		std::cout << '|';
		for ( int col = 0; col < BROAD_SIZE; ++col )
		{
			std::cout << setiosflags(ios::right);
			if ( this->board[row][col] == COM )
				std::cout << setw(3) << ComPiece;
			else if ( this->board[row][col] == HUM )
				std::cout << setw(3) << HumPiece;
			else if ( this->board[row][col] == EMPTY )
				std::cout << setw(3) << EmpPiece;
			else 
			{	
				std::cout << resetiosflags(ios::left);
				std::cerr << "invalid value(piece value), in borad[" << row + 1 << "][" << col + 1 << "]" << std::endl; 
				throw out_of_range("invalid value");
			}
		}
		std::cout << resetiosflags(ios::left);
		std::cout << '|';
		std::cout << std::endl;
	}
	std::cout << setfill('-') << setw(3 * BROAD_SIZE + 2) << std::endl;
	std::cout << "\n" << std::endl;
	return 1;
}