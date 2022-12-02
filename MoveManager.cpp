#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include "MoveManager.h"
#include "Board.h"
#include "Piece.h"

#include <Arduino.h>

int * MoveManager::validMovements(int row, int column, int* validMovesArray){
  return MoveManager::validMovements(row * 8 + column, validMovesArray);
}

int * MoveManager::validMovements(int from, int* validMovesArray) {
	
	int from_x = from % 8;
	int from_y = from / 8;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	if (piece == nullptr) {
		//std::cout << "No piece at this position" << std::endl;
		return nullptr;
	}
	Color color = piece->getColor();

	// initialize movements with -1.
	for(int i = 0; i < 64; i++){
		validMovesArray[i] = -1;
	}

  	Serial.println("Got a " + String(piece->getColor()) + " " + String(piece->getType()) + " piece");

	switch (piece->getType()) {
	case PieceType::PAWN:
		validPawnMovements(from, validMovesArray);
	case PieceType::ROOK:
		/* code */
		validRookMovements(from, validMovesArray);	
	case PieceType::KNIGHT:
		/* code */
		 validKnightMovements(from, validMovesArray);	
	case PieceType::BISHOP:
		/* code */
		validBishopMovements(from, validMovesArray);	
	case PieceType::QUEEN:
		/* code */
		validQueenMovements(from, validMovesArray);	
	case PieceType::KING:
		/* code */
		validKingMovements(from, validMovesArray);	
	default:
		return nullptr;
	}

	for (int j = 0; j < 64; j++) {
		int movement = validMovesArray[j];
		//std::cout << movement << std::endl;
		board->movePiece(from, movement);
		if (this->lookForCheck(color)) {
			validMovesArray[j] = -1;
		}
		board->movePiece(movement, from);
	}

	return validMovesArray;
}

int * MoveManager::validRookMovements(int from, int* mov_array) {
	//std::cout << "Rook" << std::endl;
	int from_x = from / 8;
	int from_y = from % 8;

	//std::cout << from_x << std::endl;
	//std::cout << from_y << std::endl;

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
			//std::cout << "No piece at " << currentIndex << std::endl;
			validIndexes[i] = currentIndex;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			//std::cout << "Enemy piece at " << currentIndex << std::endl;
			validIndexes[i] = currentIndex;
			i++;
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
			//std::cout << "Enemy piece" << std::endl;
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
			i++;
			break;
		} else {
			break;
		}
		i++;
	}


	for (int j = 0; j < i; j++) {
		currentIndex = validIndexes[j];
		//std::cout << currentIndex << std::endl;
	}

	//std::cout << "Valid indexes: " << std::endl;
	for (int j = 0; j < i; j++) {
		//std::cout << validIndexes[j] << std::endl;
	}

	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return validIndexes;
}

int * MoveManager::validKnightMovements(int from, int* mov_array) {
	//std::cout << "Knight" << std::endl;

	int from_x = from / 8;
	int from_y = from % 8;

	//std::cout << from_x << std::endl;
	//std::cout << from_y << std::endl;

	int validIndexes[8] = {-1, -1, -1, -1,-1, -1, -1, -1};

	Board * board = this->board;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();

	if (piece == nullptr) {
		//std::cout << "No piece at this position" << std::endl;
		return nullptr;
	}

	Color color = piece->getColor();

	int auxX = from_x;
	int auxY = from_y;

	int i = 0;

	if (auxX + 2 < 8 && auxY + 1 < 8) {
		auxX += 2;
		auxY += 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} 

	auxX = from_x;
	auxY = from_y;

	if (auxX + 2 < 8 && auxY - 1 >= 0) {
		auxX += 2;
		auxY -= 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX - 2 >= 0 && auxY + 1 < 8) {
		auxX -= 2;
		auxY += 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX - 2 >= 0 && auxY - 1 >= 0) {
		auxX -= 2;
		auxY -= 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX + 1 < 8 && auxY + 2 < 8) {
		auxX += 1;
		auxY += 2;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX + 1 < 8 && auxY - 2 >= 0) {
		auxX += 1;
		auxY -= 2;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX - 1 >= 0 && auxY + 2 < 8) {
		auxX -= 1;
		auxY += 2;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	auxX = from_x;
	auxY = from_y;

	if (auxX - 1 >= 0 && auxY - 2 >= 0) {
		auxX -= 1;
		auxY -= 2;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	//std::cout << "Valid indexes: " << std::endl;
	for (int j = 0; j < i; j++) {
		//std::cout << validIndexes[j] << std::endl;
	}

	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return validIndexes;
}

int * MoveManager::validBishopMovements(int from, int* mov_array) {

	//std::cout << "Bishop" << std::endl;

	int from_x = from / 8;
	int from_y = from % 8;

	//std::cout << from_x << std::endl;
	//std::cout << from_y << std::endl;

	Board * board = this->board;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();

	if (piece == nullptr) {
		//std::cout << "Piece is null" << std::endl;
		return nullptr;
	}

	Color color = piece->getColor();

	int validIndexes[7] = {-1, -1, -1, -1,-1, -1, -1};

	int auxX = from_x;
	int auxY = from_y;

	int i = 0;

	while (auxX + 1 < 8 && auxY + 1 < 8) {
		auxX += 1;
		auxY += 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
	}

	auxX = from_x;
	auxY = from_y;

	while (auxX + 1 < 8 && auxY - 1 >= 0) {
		auxX += 1;
		auxY -= 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
	}

	auxX = from_x;
	auxY = from_y;

	while (auxX - 1 >= 0 && auxY + 1 < 8) {
		auxX -= 1;
		auxY += 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
	}
	
	auxX = from_x;
	auxY = from_y;

	while (auxX - 1 >= 0 && auxY - 1 >= 0) {
		auxX -= 1;
		auxY -= 1;
		int currentIndex = auxX*8 + auxY;
		if (board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
			break;
		} else {
			break;
		}
	}


	//std::cout << "Valid indexes: " << std::endl;
	for (int j = 0; j < i; j++) {
		//std::cout << validIndexes[j] << std::endl;
	}

	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return nullptr;
}

int * MoveManager::validQueenMovements(int from, int* mov_array) {

	//std::cout << "Queen" << std::endl;

	int * validRook = validRookMovements(from, mov_array);
	int * validBishop = validBishopMovements(from, mov_array);

	int validIndexes[21] = {-1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	// int i = 0;

	// for (int j = 0; j < 7; j++) {
	// 	if (validRook[j] != -1) {
	// 		validIndexes[i] = validRook[j];
	// 		i++;
	// 	}
	// }

	// for (int j = 0; j < 7; j++) {
	// 	if (validBishop[j] != -1) {
	// 		validIndexes[i] = validBishop[j];
	// 		i++;
	// 	}
	// }
	
	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return validIndexes;
}

int * MoveManager::validKingMovements(int from, int* mov_array) {

	if (this->board->tiles[from]->getOccupiedBy() == nullptr) {
		return nullptr;
	}

	Color color = this->board->tiles[from]->getOccupiedBy()->getColor();

	int from_x = from / 8;
	int from_y = from % 8;

	int validIndexes[8] = {-1, -1, -1, -1,-1, -1, -1,-1};

	int i = 0;

	if (from_x + 1 < 8) {
		int currentIndex = (from_x + 1)*8 + (from_y);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} else if (from_x - 1 >= 0) {
		int currentIndex = (from_x - 1)*8 + (from_y);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	if (from_y + 1 < 8) {
		int currentIndex = (from_x)*8 + (from_y + 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} else if (from_y - 1 >= 0) {
		int currentIndex = (from_x)*8 + (from_y - 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	}

	if (from_x + 1 < 8 && from_y + 1 < 8) {
		int currentIndex = (from_x + 1)*8 + (from_y + 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} else if (from_x + 1 < 8 && from_y - 1 >= 0) {
		int currentIndex = (from_x + 1)*8 + (from_y - 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} else if (from_x - 1 >= 0 && from_y + 1 < 8) {
		int currentIndex = (from_x - 1)*8 + (from_y + 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} else if (from_x - 1 >= 0 && from_y - 1 >= 0) {
		int currentIndex = (from_x - 1)*8 + (from_y - 1);
		if (this->board->tiles[currentIndex]->getOccupiedBy() == nullptr) {
			validIndexes[i] = currentIndex;
			i++;
		} else if (this->board->tiles[currentIndex]->getOccupiedBy()->getColor() != color) {
			validIndexes[i] = currentIndex;
			i++;
		}
	} 

	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return validIndexes;
}

int * MoveManager::validPawnMovements(int from, int* mov_array) {
	int from_x = from / 8;
	int from_y = from % 8;

	//std::cout << from_x << std::endl;
	//std::cout << from_y << std::endl;

	int validIndexes[4] = {-1, -1, -1, -1};

	for (int i = 0; i < 4; i++) {
        //std::cout << validIndexes[i] << std::endl;
    }

	Board * b = this->board;

	Piece * piece = this->board->tiles[from]->getOccupiedBy();
	Color color = piece->getColor();

	if (color == Color::WHITE) {
		if (from_y < 7) {
			//std::cout << "y<7" << std::endl;
			if (from_x < 7) {
				//std::cout << "x<7" << std::endl;
				if (board->tiles[from + 9]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 9]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from + 9;
					}
				}
			} 
			if (from_x > 0) {
				//std::cout << "x>0" << std::endl;
				if (board->tiles[from + 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[1] = from + 7;
					}
				}
			}
			if (board->tiles[from + 1]->getOccupiedBy() == nullptr) {
				//std::cout << "frente y vazio" << std::endl;
				validIndexes[2] = from + 1;
				if (from_y == 1 && board->tiles[from + 2]->getOccupiedBy() == nullptr) {
					validIndexes[3] = from + 2;
				}
			} 
		}
	} else {

		if (from_y > 0) {
			//std::cout << "y>0" << std::endl;
			if (from_x < 7) {
				//std::cout << "x<7" << std::endl;
				if (board->tiles[from + 7]->getOccupiedBy() != nullptr) {
					if (board->tiles[from + 7]->getOccupiedBy()->getColor() == Color::BLACK) {
						validIndexes[0] = from + 7;
					}
				}
			} else if (from_x > 0) {
				//std::cout << "x>0" << std::endl;
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
        //std::cout << validIndexes[i] << std::endl;
    }

	for(int i = 0; i < sizeof(validIndexes) / sizeof(int); i++){
		if(validIndexes[i] != -1){
			mov_array[validIndexes[i]] = 1;
		}
	}

	return validIndexes;
}

bool MoveManager::lookForCheck(Color color) {
	
	int kingPosition;
	
	for (int j = 0; j<64; j++) {
		if (board->tiles[j]->getOccupiedBy() != nullptr) {
			if (board->tiles[j]->getOccupiedBy()->getType() == PieceType::KING) {
				if (board->tiles[j]->getOccupiedBy()->getColor() == color) {
					kingPosition = j;
				}
			}
		}
	}

	int x = kingPosition / 8;
	int y = kingPosition % 8;

	if (this->board->tiles[kingPosition]->getOccupiedBy() == nullptr || this->board->tiles[kingPosition]->getOccupiedBy()->getType() != PieceType::KING) {
		return false;
	}
	Color kingColor = this->board->tiles[kingPosition]->getOccupiedBy()->getColor();

	int i = 0;

	for (int j = 0; j < 64; j++) {
		if (board->tiles[j]->getOccupiedBy() != nullptr) {
			if (board->tiles[j]->getOccupiedBy()->getColor() != kingColor) {
				int * movements;
				validMovements(j, movements); 
				for (int k = 0; k < 21; k++) {
					if (movements[k] == kingPosition) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

MoveManager * MoveManager::moveManagerInstance = nullptr;
