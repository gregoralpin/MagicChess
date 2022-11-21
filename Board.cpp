#pragma GCC diagnostic ignored "-Wc++11-extensions"


#include<iostream>
#include "Board.h"

static Board * GetBoardInstance() {
    Board * instance = Board::boardInstance;
    if (instance == nullptr) {
        instance = new Board();
        Board::boardInstance = instance;
    }
    instance->setTiles();
    return instance;
}

void Board::setTiles() {
    for (int i = 0; i < 64; i++) {
        if (i%8 == 0) {
            if (i/8 == 0 || i/8 == 7) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::ROOK, Color::WHITE));
            } else if (i/8 == 1 || i/8 == 6) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::KNIGHT, Color::WHITE));
            } else if (i/8 == 2 || i/8 == 5) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::BISHOP, Color::WHITE));
            } else if (i/8 == 3) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::QUEEN, Color::WHITE));
            } else {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::KING, Color::WHITE));
            }
        } else if (i%8 == 1) {
            tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::PAWN, Color::WHITE));
        } else if (i%8 == 6) {
            tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::PAWN, Color::BLACK));
        } else if (i%8 == 7) {
            if (i/8 == 0 || i/8 == 7) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::ROOK, Color::BLACK));
            } else if (i/8 == 1 || i/8 == 6) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::KNIGHT, Color::BLACK));
            } else if (i/8 == 2 || i/8 == 5) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::BISHOP, Color::BLACK));
            } else if (i/8 == 3) {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::QUEEN, Color::BLACK));
            } else {
                tiles[i] = new Tile(i%8, i/8, new Piece(PieceType::KING, Color::BLACK));
            }
        } else {
            tiles[i] = new Tile(i % 8, i / 8);
        }
    }
}

void Board::movePiece(int from, int to) {
    tiles[to]->setOccupiedBy(tiles[from]->getOccupiedBy());
    tiles[from]->setOccupiedBy(nullptr);
}