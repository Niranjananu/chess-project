#include <iostream>
#include "board.hpp"
 
void test_rook();
void test_knight(); 
void test_bishop();
void test_queen();
void test_pawn(); 
void test_king();  
void test_rook_and_king();
 
int main() 
{
    std::cout << "Chess pieces module loaded successfully.\n" << std::endl;
    
    // some tests:

    // rook
    test_rook();

    //king
    test_king();


    //combo tests
    test_rook_and_king();

    std::cin.get(); // this keeps the console window open until a key is pressed
    return 0;
}

void test_rook()
{
    // rook
    rook test_rook("a1", true);

    if(test_rook.give_location() == "a1" && test_rook.get_is_white() == true)
    {
        std::cout << "Rook make tests passed." << std::endl;
    }
    else
    {
        std::cout << "Rook make tests failed." << std::endl;
    }
    test_rook.set_destination("a4");
    if(test_rook.get_destination() == "a4")
    {
        std::cout << "Rook destination set correctly." << std::endl;
    }
    else
    {
        std::cout << "Rook destination not set correctly." << std::endl;
    }
    MoveResult result = test_rook.is_move_ok("R#####rr########################################################0");
    if(result == MoveResult::Valid_Checkmate)
    {
        std::cout << "Rook move validation passed." << std::endl;
    }
    else
    {
        std::cout << "got: " << std::endl;
        std::cout << result << std::endl;
        std::cout << "Rook move validation failed." << std::endl;
    }   
    test_rook.move();
    if(test_rook.give_location() == "a4")
    {
        std::cout << "Rook move executed correctly." << std::endl;
    }
    else
    {
        std::cout << "Rook move execution failed." << std::endl;
    }
    // end of tests for rook
}
void test_knight()
{

}
void test_bishop()
{

}
void test_queen()
{

}
void test_pawn()
{

}
void test_king()
{
    // king
    king test_king("a1", true);

    if(test_king.give_location() == "a1" && test_king.get_is_white() == true)
    {
        std::cout << "king make tests passed." << std::endl;
    }
    else
    {
        std::cout << "king make tests failed." << std::endl;
    }
    test_king.set_destination("b1");
    if(test_king.get_destination() == "b1")
    {
        std::cout << "king destination set correctly." << std::endl;
    }
    else
    {
        std::cout << "king destination not set correctly." << std::endl;
    }
    MoveResult result = test_king.is_move_ok("K###############################################################0");
    if(result == MoveResult::Valid_Checkmate)
    {
        std::cout << "king move validation passed." << std::endl;
    }
    else
    {
        std::cout << "got: " << std::endl;
        std::cout << result << std::endl;
        std::cout << "king move validation failed." << std::endl;
    }   
    test_king.move();
    if(test_king.give_location() == "b1")
    {
        std::cout << "king move executed correctly." << std::endl;
    }
    else
    {
        std::cout << "king move execution failed." << std::endl;
    }
    test_king.set_destination("c1");
    result = test_king.is_move_ok("#K#######################################k######################0");
    if(result == MoveResult::Valid)
    {
        std::cout << "king move validation 2 passed." << std::endl;
    }
    else
    {
        std::cout << "got: " << std::endl;
        std::cout << result << std::endl;
        std::cout << "king move validation 2 failed." << std::endl;
    } 
    test_king.set_destination("a1");
    result = test_king.is_move_ok("kK##############################################################0");
    if(result == MoveResult::Valid_Checkmate)
    {
        std::cout << "king move validation 3 passed." << std::endl;
    }
    else
    {
        std::cout << "got: " << std::endl;
        std::cout << result << std::endl;
        std::cout << "king move validation 3 failed." << std::endl;
    }   

    // end of tests for king
}

void test_rook_and_king()
{
    std::cout << "=== Rook + King endgame test ===" << std::endl;

    // Board layout (remember: index = (rank-1)*8 + file):
    // Index 0-7   = rank 1 (a1-h1)
    // Index 56-63 = rank 8 (a8-h8)
    
    // Initial position:
    // White: Rook a1 (index 0), King e1 (index 4)
    // Black: King e8 (index 60)
    std::string board =
        "R###K###"   // rank 1: White Rook a1, White King e1
        "########"   // rank 2
        "########"   // rank 3
        "########"   // rank 4
        "########"   // rank 5
        "########"   // rank 6
        "########"   // rank 7
        "####k###"   // rank 8: black king e8 (index 60)
        "0";         // white to move

    king w_king("e1", true);
    rook w_rook("a1", true);
    king b_king("e8", false);

    std::cout << "Initial board:\n" << board << std::endl;

    // Move 1: White rook a1 -> a8
    w_rook.set_destination("a8");
    MoveResult result = w_rook.is_move_ok(board);

    std::cout << "Move 1: White rook a1 -> a8: " << result;
    if (result == MoveResult::Valid_Check) {
        std::cout << " ✓ (Valid_Check)" << std::endl;
    } else {
        std::cout << " ✗ (Expected 1=Valid_Check)" << std::endl;
    }

    // Update board: move rook from a1 (0) to a8 (56)
    board[0] = '#';    // Clear a1
    board[56] = 'R';   // Place rook at a8
    board[64] = '1';   // Black to move
    w_rook.move();

    std::cout << "Board after move 1:\n" << board << std::endl;

    // Move 2: Black king e8 -> d8 (should be Invalid_SelfCheck)
    b_king.set_destination("d8");
    result = b_king.is_move_ok(board);

    std::cout << "Move 2: Black king e8 -> d8: " << result;
    if (result == MoveResult::Invalid_SelfCheck) {
        std::cout << " ✓ (Invalid_SelfCheck - can't move into check)" << std::endl;
    } else {
        std::cout << " ✗ (Expected 4=Invalid_SelfCheck)" << std::endl;
    }

    // Move 2 alternative: Black king e8 -> f7 (valid escape)
    b_king.set_destination("f7");
    result = b_king.is_move_ok(board);

    std::cout << "Move 2 alt: Black king e8 -> f7: " << result;
    if (result == MoveResult::Valid) {
        std::cout << " ✓ (Valid)" << std::endl;
        board[60] = '#';   // Clear e8 (60 = (8-1)*8 + 4)
        board[53] = 'k';   // Place king at f7 (53 = (7-1)*8 + 5)
        board[64] = '0';   // White to move
        b_king.move();
    } else {
        std::cout << " ✗ (Expected 0=Valid)" << std::endl;
    }

    std::cout << "Board after move 2:\n" << board << std::endl;

    // Move 3: White king e1 -> e2
    w_king.set_destination("e2");
    result = w_king.is_move_ok(board);

    std::cout << "Move 3: White king e1 -> e2: " << result;
    if (result == MoveResult::Valid) {
        std::cout << " ✓ (Valid)" << std::endl;
        board[4] = '#';    // Clear e1
        board[12] = 'K';   // Place king at e2
        board[64] = '1';   // Black to move
        w_king.move();
    } else {
        std::cout << " ✗ (Expected 0=Valid)" << std::endl;
    }

    std::cout << "Board after move 3:\n" << board << std::endl;

    // Move 4: White rook a8 -> f8 (should capture or threaten)
    w_rook.set_destination("f8");
    result = w_rook.is_move_ok(board);

    std::cout << "Move 4: White rook a8 -> f8: " << result;
    if (result == MoveResult::Valid_Check || result == MoveResult::Valid) {
        std::cout << " ✓ (result=" << result << ")" << std::endl;
    } else {
        std::cout << " ✗ (Unexpected result)" << std::endl;
    }

    std::cout << "=== End of test ===" << std::endl;
}