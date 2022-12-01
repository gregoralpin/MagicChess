#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"

int main() {
    Board* board = Board::GetBoardInstance();
    board->mockUpgradePawnBoard();
    board->printBoard();
    
    MoveManager * moveManager = MoveManager::GetMoveManagerInstance();

    board->movePiece(6,7);
    board->movePiece(57,56);
    board->printBoard();

    // std::cout << "Is Check: " << isCheck << std::endl;
    return 0;
}