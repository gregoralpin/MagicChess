#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"

int main() {
    Board* board = new Board();// = Board::GetBoardInstance();
    board->setTiles();

    
    MoveManager * moveManager = MoveManager::GetMoveManagerInstance();
    moveManager->testCpp();

    //int * moves = moveManager->validPawnMovements(8);


    // std::cout << moveManager->test() << std::endl;
    return 0;
}