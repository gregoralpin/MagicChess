#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"

int main() {
    Board* board = Board::GetBoardInstance();
    board->mockRookBoard();
    board->printBoard();
    
    MoveManager * moveManager = MoveManager::GetMoveManagerInstance();

    int * moves = moveManager->validMovements(24);

    bool isCheck = moveManager->lookForCheck(Color::WHITE);

    std::cout << "Is Check: " << isCheck << std::endl;
    return 0;
}