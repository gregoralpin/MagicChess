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

  int * validMovements(int row, int column,  int* validMovesArray);

	int * validMovements(int from,  int* validMovesArray);

	int * validPawnMovements(int from, int* mov_array);

	int * validRookMovements(int from, int* mov_array);

	int * validKnightMovements(int from, int* mov_array);

	int * validBishopMovements(int from, int* mov_array);

	int * validQueenMovements(int from, int* mov_array);

    int * validKingMovements(int from, int* mov_array);
	
	bool lookForCheck(Color color);
};
