#ifndef CLASS_CHESS_P_HPP
#define CLASS_CHESS_P_HPP

#include <iostream> // for std::string and other I/O operations

enum MoveResult 
{
    Valid = 0,
    Valid_Check = 1,
    Invalid_NoPieceAtSource = 2,
    Invalid_DestinationOccupiedByOwnPiece = 3,
    Invalid_SelfCheck = 4,
    Invalid_IndexOutOfRange = 5,
    Invalid_IllegalMovement = 6,
    Invalid_SameSourceAndDestination = 7,
    Valid_Checkmate = 8
} 
moveResult;

/*
// Class definition for chess pieces 
// ------------------------------------------
// This class serves as a base class for all chess pieces
// It contains common attributes and methods that all chess pieces share
*/
// --- Class Definition --- //
class chess_p 
{
private:
    // Private member variables
    std::string location; // get set in chess_p constructor
    std::string destination; // get set in set_destination method
    bool is_white; // get set in chess_p constructor
    bool is_alive; // is set to true in chess_p constructor

public:
    // Public methods

    // -- Constructor --//

    chess_p(std::string loc, bool is_it_white); // loc: initial location, color: true for white, false for black

    // --- Getters --- //

    bool get_is_alive(); // returns is_alive status
    bool get_is_white(); // returns is_white status
    std::string get_destination(); // returns destination location

    // --- Setters --- //

    void set_destination(std::string try_move); // try_move: proposed destination location
    void set_die(); // turns is_alive from true to false 

    // --- Other Methods --- //

    void move(); // updates location to destination if move is valid
    std::string give_location(); // returns current location of the piece
    bool chess_p::is_there_check(std::string state_of_board, char turn);


    // --- Virtual Methods --- //

    virtual MoveResult is_move_ok(std::string state_of_board ) = 0; // state_of_board: current state of the chess board

};

#endif // CLASS_CHESS_P_HPP