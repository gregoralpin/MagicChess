#include "Piece.h"

Piece::Piece(PieceType type, Color color) {
	this->color = color;
	this->type = type;
}

PieceType Piece::getType() {
	return this->type;
}

Color Piece::getColor() {
	return this->color;
}

void Piece::upgrade(PieceType type) {
	this->type = type;
}
