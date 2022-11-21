#pragma GCC diagnostic ignored "-Wc++11-extensions"

#include <iostream>
#include "MoveManager.h"
#include "Board.h"
#include "Piece.h"

int * MoveManager::validMovements(int from) {
	
	int from_x = from % 8;
	int from_y = from / 8;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	if (piece == nullptr) {
		std::cout << "No piece at this position" << std::endl;
		return nullptr;
	}
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
	std::cout << "Rook" << std::endl;
	int from_x = from % 8;
	int from_y = from / 8;

	std::cout << from_x << std::endl;
	std::cout << from_y << std::endl;

	int * validIndexes = new int[14];

	Board * board = this->board;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	Color color = piece->getColor();

	int auxX = from_x;
	int auxY = from_y;

	int i = 0;
	int currentIndex = auxX*8 + auxY;
	while (auxX < 7) {
		auxX++;
		currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			break;
		} else {
			break;
		}
		i++;
	}

	auxX = from_x;

	while (auxX > 0) {
		auxX--;
		currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
		i++;
	}

	auxX = from_x;

	while (auxY < 7) {
		auxY++;
		currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			std::cout << "Enemy piece" << std::endl;
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
		i++;
	}

	auxY = from_y;

	while (auxY > 0) {
		auxY--;
		currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			break;
		} else {
			break;
		}
		i++;
	}

	std::cout << "Valid indexes: " << std::endl;
	for (int j = 0; j < i; j++) {
		std::cout << validIndexes[j] << std::endl;
	}
	return validIndexes;
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
	int from_x = from / 8;
	int from_y = from % 8;

	std::cout << from_x << std::endl;
	std::cout << from_y << std::endl;

	int validIndexes[4] = {-1, -1, -1, -1};

	for (int i = 0; i < 4; i++) {
        std::cout << validIndexes[i] << std::endl;
    }

	Board * b = this->board;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	Color color = piece->getColor();

	if (color == Color::WHITE) {
		if (from_y < 7) {
			std::cout << "y<7" << std::endl;
			if (from_x < 7) {
				std::cout << "x<7" << std::endl;
				if (board->tiles[from + 9]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 9]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from + 9;
					}
				}
			} 
			if (from_x > 0) {
				std::cout << "x>0" << std::endl;
				if (board->tiles[from + 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[1] = from + 7;
					}
				}
			}
			if (board->tiles[from + 1]->getOccupiedBy() == nullptr) {
				std::cout << "frente y vazio" << std::endl;
				validIndexes[2] = from + 1;
				if (from_y == 1 && board->tiles[from + 2]->getOccupiedBy() == nullptr) {
					validIndexes[3] = from + 2;
				}
			} 
		}
	} else {

		if (from_y > 0) {
			std::cout << "y>0" << std::endl;
			if (from_x < 7) {
				std::cout << "x<7" << std::endl;
				if (board->tiles[from + 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from + 7;
					}
				}
			} else if (from_x > 0) {
				std::cout << "x>0" << std::endl;
				if (board->tiles[from - 9]->getOccupiedBy() != nullptr) {
					if (board->tiles[from - 9]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[1] = from - 9;
					}
				}
			}
			if (board->tiles[from - 1]->getOccupiedBy() == nullptr) {
				validIndexes[2] = from - 1;
				if (from_y == 6 && board->tiles[from - 2]->getOccupiedBy() == nullptr) {
					validIndexes[3] = from - 2;
				}
			} 
		}
	}

	for (int i = 0; i < 4; i++) {
        std::cout << validIndexes[i] << std::endl;
    }
	return validIndexes;
}

MoveManager * MoveManager::moveManagerInstance = nullptr;