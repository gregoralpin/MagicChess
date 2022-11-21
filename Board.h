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
		//boardInstance = (this);
	};

	static Board * GetBoardInstance() {
		static Board * instance = new Board();
		if (boardInstance == nullptr) {
			boardInstance = new Board();
		}
		return boardInstance;
	};

	void printBoard() {
		for (int i = 0; i < 64; i++) {
			tiles[i]->printTile();
		}
	}
};
