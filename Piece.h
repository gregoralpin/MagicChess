#pragma once
#include<string>

enum Color { 
	BLACK = 0,
	WHITE = 1
};

enum PieceType {
	PAWN = 0,
	ROOK = 1,
	KNIGHT = 2,
	BISHOP = 3,
	QUEEN = 4,
	KING = 5
};

static const char* PieceTypeNames[] = { "PAWN", "ROOK", "KNIGHT", "BISHOP", "QUEEN", "KING" };
static const char* ColorNames[] = { "BLACK", "WHITE" };

class Piece {

	private:
		PieceType type;
		Color color;

	public:
		PieceType getType();

		Color getColor();

		void upgrade(PieceType type);

		Piece(PieceType type, Color color);

		std::string getName() {
			PieceType pt = getType();
			Color c = getColor();
			return std::string("Piece of type ") + PieceTypeNames[pt] + std::string(" and color ") + ColorNames[c];
		}
};