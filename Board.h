#pragma once
#include "Piece.h"
#include "Tile.h"

class Board {

public:

	Tile * tiles[64];

	static Board* boardInstance;
	
	void setTiles();

	void movePiece(int from, int to);
	
	Board() {
		std::cout << "Board constructor called" << std::endl;
		setTiles();
	};

	static Board * GetBoardInstance() {
		if (boardInstance == nullptr) {
			boardInstance = new Board();
			boardInstance->setTiles();
		}
		return boardInstance;
	};

	void printBoard() {
		for (int i = 0; i < 64; i++) {
			tiles[i]->printTile();
		}
	}

	void mockRookBoard();

};
