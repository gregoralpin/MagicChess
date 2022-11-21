#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"

int main() {
    Board* board = new Board();// = Board::GetBoardInstance();
    board->setTiles();
    board->printBoard();

    MoveManager * moveManager = MoveManager::GetMoveManagerInstance();
    // int * moves = moveManager->validPawnMovements(8);
    std::cout << "Hello World!\n";
    return 0;
}