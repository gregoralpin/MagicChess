#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"

int main() {
    Board* board = Board::GetBoardInstance();
    board->mockRookBoard();
    board->printBoard();
    
    MoveManager * moveManager = MoveManager::GetMoveManagerInstance();

    int * moves = moveManager->validMovements(63);
    

    // std::cout << moveManager->test() << std::endl;
    return 0;
}