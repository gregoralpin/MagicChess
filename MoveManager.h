#pragma once
#include "Board.h"
#include "Piece.h"
#include <iostream>

class MoveManager {


private:
    

	MoveManager() {
		std::cout << "MoveManager constructor called" << std::endl;
		//this->board = Board::GetBoardInstance();
	}


	
public:
	
	static MoveManager * moveManagerInstance;

	MoveManager(MoveManager &other) = delete;

	void operator=(const MoveManager &) = delete;

    Board * board;	


	static MoveManager * GetMoveManagerInstance() {
		if (moveManagerInstance == nullptr) {
			// moveManagerInstance = new MoveManager();
			return nullptr;
		} else {
		// 	std::cout << "MoveManager instance already exists" << std::endl;
			return nullptr;
		}
	}

	int * validMovements(int from);

	int * validPawnMovements(int from);

	int * validRookMovements(int from);

	int * validKnightMovements(int from);

	int * validBishopMovements(int from);

	int * validQueenMovements(int from);

    int * validKingMovements(int from);
	
};

MoveManager * MoveManager::moveManagerInstance = nullptr;