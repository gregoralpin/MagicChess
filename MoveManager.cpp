#include <iostream>
#include "MoveManager.h"
#include "Board.h"
#include "Piece.h"

void MoveManager::testCpp() {
	std::cout << "testCpp called" << std::endl;
}

int * MoveManager::validMovements(int from) {
	
	int from_x = from % 8;
	int from_y = from / 8;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	Color color = piece->getColor();

	switch (piece->getType()) {
	case PieceType::PAWN:
		return validPawnMovements(from);
	case PieceType::ROOK:
		/* code */
		return validRookMovements(from);	
	case PieceType::KNIGHT:
		/* code */
		return validKnightMovements(from);	
	case PieceType::BISHOP:
		/* code */
		return validBishopMovements(from);	
	case PieceType::QUEEN:
		/* code */
		return validQueenMovements(from);	
	case PieceType::KING:
		/* code */
		return validKingMovements(from);	
	
	default:
		return nullptr;
	}
}

int * MoveManager::validRookMovements(int from) {

	return nullptr;
}

int * MoveManager::validKnightMovements(int from) {

	return nullptr;
}

int * MoveManager::validBishopMovements(int from) {

	return nullptr;
}

int * MoveManager::validQueenMovements(int from) {

	return nullptr;
}

int * MoveManager::validKingMovements(int from) {

	return nullptr;
}

int * MoveManager::validPawnMovements(int from) {
	int from_y = from % 8;
	int from_x = from / 8;

	int validIndexes[4] = {-1, -1, -1, -1};

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	Color color = piece->getColor();

	if (color == Color::WHITE) {
		if (from_y < 7) {
			if (from_x < 7) {
				if (board->tiles[from + 9]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 9]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from + 9;
					}
				}
			} else if (from_x > 0) {
				if (board->tiles[from + 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[1] = from + 7;
					}
				}
			}
			if (board->tiles[from + 8]->getOccupiedBy() == nullptr) {
				validIndexes[2] = from + 8;
				if (from_x == 1 && board->tiles[from + 16]->getOccupiedBy() == nullptr) {
					validIndexes[3] = from + 16;
				}
			} 
		}
	} else {
		if (from_y > 0) {
			if (from_x < 7) {
				if (board->tiles[from - 9]->getOccupiedBy() != nullptr) {
					if (board->tiles[from - 9]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from - 9;
					}
				}
			} else if (from_x > 0) {
				if (board->tiles[from - 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from - 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[1] = from - 7;
					}
				}
			}
			if (board->tiles[from + 8]->getOccupiedBy() == nullptr) {
				validIndexes[2] = from - 8;
				if (from_x == 1 && board->tiles[from + 16]->getOccupiedBy() == nullptr) {
					validIndexes[3] = from - 16;
				}
			} 
		}
	}
	return nullptr;
}

MoveManager * MoveManager::moveManagerInstance = nullptr;