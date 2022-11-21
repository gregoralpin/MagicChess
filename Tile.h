#include <iostream>
#include "Piece.h"

class Tile {
	
	private:
		int x, y;
		Piece* occupiedBy;

		int* getCoordinates();


	public:
		Tile(int x, int y);

		Tile(int x, int y, Piece* piece);
		
		Piece* getOccupiedBy();

		void setOccupiedBy(Piece* piece);

		void printTile() {
			if (occupiedBy == nullptr) {
				std::cout << "Tile at " << x << ", " << y << " is empty" << std::endl;
			} else {
				std::cout << "Tile at (" << x << ", " << y << ") is occupied by " << occupiedBy->getName() << std::endl;
			}
		}
};