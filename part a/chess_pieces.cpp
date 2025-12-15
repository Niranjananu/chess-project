// filepath: chess_project\part a\chess_pieces.cpp

#include "chess_pieces.hpp"

// --- Rook Constructor --- //
/*
^   * fanction name:        rook::rook
---------------------------------------------------------------------------------------
    * fanction description: Initializes a Rook chess piece with its starting location and color.
    * fanction input:       const std::string& start_loc, bool is_it_white
        - start_loc:        The starting location of the Rook piece.
        - is_it_white:      Indicates whether the piece is white (true) or black (false).
    * fanction output:      void
    * return value:         None.
    * eficency:             O(1) - constant time complexity.
---------------------------------------------------------------------------------------
*/
rook::rook(const std::string& start_loc, bool is_it_white) : chess_p(start_loc, is_it_white){}

MoveResult rook::is_move_ok(std::string state_of_board)
{
    // format of state_of_board is the first 64 characters represent the board squares from a1 to h8
    // and the 65th character represents whose turn it is (0 for white, other for black)
    // and the 66th character is null terminator
    // # represents an empty square
    /*
    the return values are:
    Valid = 0,
    Valid_Check = 1,
    Invalid_NoPieceAtSource = 2,
    Invalid_DestinationOccupiedByOwnPiece = 3,
    Invalid_SelfCheck = 4,
    Invalid_IndexOutOfRange = 5,
    Invalid_IllegalMovement = 6,
    Invalid_SameSourceAndDestination = 7,
    Valid_Checkmate = 8
    */

    std::string loc = give_location();                       // current location
    std::string dest = get_destination();                    // proposed destination
    char turn = state_of_board[64];                          // whose turn it is
    MoveResult result = MoveResult::Invalid_IllegalMovement; // default to illegal movement
    int source_index = 0;                                    // index of source square
    int dest_index = 0;                                      // index of destination square
    char dest_piece = '#';                                   // piece at destination
    int start_index = 0;                                     // starting index for path checking
    int end_index = 0;                                       // ending index for path checking
    int step = 0;                                            // step for path checking

    // code number 7
    // Check for same source and destination
    if (loc == dest)
    {
        result = MoveResult::Invalid_SameSourceAndDestination;
        return result;
    }

    // code number 2
    // check for no piece at source
    source_index = (loc[1] - '1') * 8 + (loc[0] - 'a'); // the logic to convert loc like "a1" to index 0-63
    if (state_of_board[source_index] == '#')            // check if there's no piece at source
    {
        result = MoveResult::Invalid_NoPieceAtSource;
        return result;
    }

    // code number 3
    // check for destination occupied by own piece
    dest_index = (dest[1] - '1') * 8 + (dest[0] - 'a');
    if (state_of_board[dest_index] != '#')
    {
        // Determine if the piece at destination is of the same color
        char dest_piece = state_of_board[dest_index];
        bool dest_is_white = (dest_piece >= 'A' && dest_piece <= 'Z'); // Assuming uppercase letters represent white pieces
        if (dest_is_white == get_is_white())
        {
            result = MoveResult::Invalid_DestinationOccupiedByOwnPiece;
            return result;
        }
    }

    // code number 5
    // Check for index out of range
    if (source_index < 0 || source_index >= 64 || dest_index < 0 || dest_index >= 64)
    {
        result = MoveResult::Invalid_IndexOutOfRange;
        return result;
    }

    // code number 6
    // Check for legal rook movement
    // Check if it's the correct turn for the piece color
    if ((turn == '0' && get_is_white()) || (turn != '0' && !get_is_white()))
    {
        // Rook moves in straight lines either horizontally or vertically
        if (loc[0] == dest[0] || loc[1] == dest[1])
        {
            // Check if the path is clear
            start_index = (loc[1] - '1') * 8 + (loc[0] - 'a'); // the logic to convert loc like "a1" to index 0-63
            end_index = (dest[1] - '1') * 8 + (dest[0] - 'a'); // the logic to convert dest like "a1" to index 0-63
            if (loc[0] == dest[0]) // vertical move
            {
                if (loc[1] < dest[1]) // check direction
                {
                    step = 8;  // move up the board
                }
                else
                {
                    step = -8; // move down the board
                }
            }
            else // horizontal move
            {
                if (loc[0] < dest[0])
                {
                    step = 1;  // move right on the board
                }
                else
                {
                    step = -1; // move left on the board
                }
            }
            for (int i = start_index + step; i != end_index; i += step)
            {
                if (state_of_board[i] != '#') // If there's a piece in the path, it's not a valid move
                {
                    result = MoveResult::Invalid_IllegalMovement;
                    return result;
                }
            }
            result = MoveResult::Valid;
        }
        else
        {
            result = MoveResult::Invalid_IllegalMovement;
            return result; // Not a valid rook move
        }
    }
    else
    {
        result = MoveResult::Invalid_IllegalMovement;
        return result; // Not the correct turn
    }

    // code number 4
    // check for self check
    // (This requires simulating the move and checking if it puts own king in check)
    

    return result;
}
