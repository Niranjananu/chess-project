#include "board.hpp"
#include <iostream>

board::board() 
{
    int i = 0;
    int j = 0;
    char file = '\0';
    std::string pos = "";

    // Initialize the chess board with pieces in starting positions
    state_of_board_as_string = STARTING_BOARD_STATE;

    // Initialize the chess_board array with nullptrs
    for (i = 0; i < BOARD_SIZE_UP; ++i)
    {
        for (j = 0; j < BOARD_SIZE_RIGHT; ++j)
        {
            chess_board[i][j] = nullptr;
        }
    }

    // Place black pieces (row 0 = rank 8)
    chess_board[0][0] = new rook("a8", false);   // Black Rook (false = black)
    chess_board[0][1] = new knight("b8", false);
    chess_board[0][2] = new bishop("c8", false);
    chess_board[0][3] = new queen("d8", false);
    chess_board[0][4] = new king("e8", false);
    chess_board[0][5] = new bishop("f8", false);
    chess_board[0][6] = new knight("g8", false);
    chess_board[0][7] = new rook("h8", false);
    
    // Black pawns (row 1 = rank 7)
    for (j = 0; j < BOARD_SIZE_RIGHT; ++j)
    {
        file = 'a' + j;
        pos = "";
        pos += file;
        pos += '7';  // FIXED: rank 7, not 2
        chess_board[1][j] = new pawn(pos, false);
    }

    // Place white pieces (row 7 = rank 1)
    chess_board[7][0] = new rook("a1", true);   // White Rook (true = white)
    chess_board[7][1] = new knight("b1", true);
    chess_board[7][2] = new bishop("c1", true);
    chess_board[7][3] = new queen("d1", true);
    chess_board[7][4] = new king("e1", true);
    chess_board[7][5] = new bishop("f1", true);
    chess_board[7][6] = new knight("g1", true);
    chess_board[7][7] = new rook("h1", true);
    
    // White pawns (row 6 = rank 2)
    for (j = 0; j < BOARD_SIZE_RIGHT; ++j)
    {
        file = 'a' + j;
        pos = "";
        pos += file;
        pos += '2';  // FIXED: rank 2, not 7
        chess_board[6][j] = new pawn(pos, true);
    }
}


// Destructor to clean up dynamically allocated pieces
board::~board()
{ 
	int i = 0;
	int j = 0;
	for (i = 0; i < BOARD_SIZE_UP; ++i)
	{
		for (j = 0; j < BOARD_SIZE_RIGHT; ++j)
		{
			delete chess_board[i][j]; // Delete each piece if it exists
			chess_board[i][j] = nullptr; // Set pointer to nullptr after deletion
		}
	}
}

bool board::kill(chess_p* p_chess)
{
	std::string des = p_chess->get_destination();

	int col = des[0] - 'a';
	int row = des[1] - '1';

	if (chess_board[row][col] != nullptr)
	{
		delete chess_board[row][col];
		chess_board[row][col] = nullptr;
		return true;
	}

	return false;
}
