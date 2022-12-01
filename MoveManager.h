#pragma once
#include "Board.h"
#include "Piece.h"

class MoveManager {

private:
	MoveManager() {
		//std::cout << "MoveManager constructor called" << std::endl;
	}
	
public:
	void test() {
		//std::cout << "MoveManager test called" << std::endl;
	}

	void testCpp();

	static MoveManager * moveManagerInstance;

	MoveManager(MoveManager &other) = delete;

	void operator=(const MoveManager &) = delete;

    Board * board;	


	static MoveManager * GetMoveManagerInstance() {
		if (moveManagerInstance == nullptr) {
			//std::cout << "MoveManager instance dont exists" << std::endl;
			moveManagerInstance = new MoveManager();
			moveManagerInstance->board = Board::GetBoardInstance();
			//std::cout << "Board Added" << std::endl;

		} else {
			//std::cout << "MoveManager instance already exists" << std::endl;
		}
		return moveManagerInstance;
	}

  int * validMovements(int row, int column);

	int * validMovements(int from);

	int * validPawnMovements(int from);

	int * validRookMovements(int from);

	int * validKnightMovements(int from);

	int * validBishopMovements(int from);

	int * validQueenMovements(int from);

    int * validKingMovements(int from);
	
	bool lookForCheck(Color color);
};
