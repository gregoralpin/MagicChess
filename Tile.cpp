#include "Tile.h"

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
}

Tile::Tile(int x, int y, Piece* piece) {
    this->x = x;
    this->y = y;
    this->occupiedBy = piece;
}


int* Tile::getCoordinates()
{
	int * coord = (int *)malloc(2 * sizeof(int));
    coord[0] = this->x;
    coord[1] = this->y;
	return coord;
}

Piece* Tile::getOccupiedBy() {
	return this->occupiedBy;
}

void Tile::setOccupiedBy(Piece* piece) {
	this->occupiedBy = piece;
}

