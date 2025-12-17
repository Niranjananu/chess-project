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

    // Board layout:
    // Indices 0-7   = rank 8
    // Indices 8-15  = rank 7
    // Indices 16-23 = rank 6
    // Indices 24-31 = rank 5
    // Indices 32-39 = rank 4
    // Indices 40-47 = rank 3
    // Indices 48-55 = rank 2
    // Indices 56-63 = rank 1

    std::string board =
        "####k###"   // rank 8 (0-7): black king on e8 (index 4)
        "########"   // rank 7 (8-15)
        "########"   // rank 6 (16-23)
        "########"   // rank 5 (24-31)
        "########"   // rank 4 (32-39)
        "########"   // rank 3 (40-47)
        "########"   // rank 2 (48-55)
        "R###K###"   // rank 1 (56-63): white rook on a1 (56), white king on e1 (60)
        "0";         // white to move

    king w_king("e1", true);
    rook w_rook("a1", true);
    king b_king("e8", false);

    std::cout << "Initial board:\n" << board << std::endl;

    // Move 1: White rook a1 -> a8
    w_rook.set_destination("a8");
    MoveResult result = w_rook.is_move_ok(board);

    std::cout << "White rook a1 -> a8: " << result;
    if (result == MoveResult::Valid_Check) {
        std::cout << " (Valid_Check - PASS)" << std::endl;
    } else {
        std::cout << " (Expected Valid_Check=1, FAIL)" << std::endl;
    }

    // Update board manually
    board[56] = '#';   // Clear a1
    board[0] = 'R';    // Place rook at a8
    board[64] = '1';   // Black to move
    w_rook.move();

    std::cout << "Board after move 1:\n" << board << std::endl;

    // Move 2: Black king e8 -> d8 (should be Invalid_SelfCheck)
    b_king.set_destination("d8");
    result = b_king.is_move_ok(board);

    std::cout << "Black king e8 -> d8: " << result;
    if (result == MoveResult::Invalid_SelfCheck) {
        std::cout << " (Invalid_SelfCheck - PASS)" << std::endl;
    } else {
        std::cout << " (Expected Invalid_SelfCheck=4, FAIL)" << std::endl;
    }

    // Move 2 alternative: Black king e8 -> f8
    b_king.set_destination("f8");
    result = b_king.is_move_ok(board);

    std::cout << "Black king e8 -> f8: " << result;
    if (result == MoveResult::Valid) {
        std::cout << " (Valid - PASS)" << std::endl;
        board[4] = '#';    // Clear e8
        board[5] = 'k';    // Place king at f8
        board[64] = '0';   // White to move
        b_king.move();
    } else {
        std::cout << " (Expected Valid=0, FAIL)" << std::endl;
    }

    std::cout << "Board after move 2:\n" << board << std::endl;

    // Move 3: White rook a8 -> f8 (captures king)
    w_rook.set_destination("f8");
    result = w_rook.is_move_ok(board);

    std::cout << "White rook a8 -> f8: " << result;
    if (result == MoveResult::Valid_Checkmate) {
        std::cout << " (Valid_Checkmate - PASS)" << std::endl;
    } else {
        std::cout << " (Expected Valid_Checkmate=8, FAIL)" << std::endl;
    }

    std::cout << "=== End of test ===" << std::endl;
}