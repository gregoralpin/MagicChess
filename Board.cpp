#pragma GCC diagnostic ignored "-Wc++11-extensions"

#include<iostream>
#include "Board.h"

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

Board* Board::boardInstance = nullptr;

void Board::mockRookBoard() {
    for (int i = 0; i < 63; i++) {
        tiles[i] = new Tile(i/8, i%8);
    }

    tiles[0] = new Tile(0, 0, new Piece(PieceType::ROOK, Color::WHITE));
    tiles[2] = new Tile(0, 2, new Piece(PieceType::ROOK, Color::WHITE));
    tiles[7] = new Tile(0, 7, new Piece(PieceType::PAWN, Color::BLACK));
    tiles[8] = new Tile(1, 0, new Piece(PieceType::KNIGHT, Color::WHITE));
    tiles[15] = new Tile(1, 7, new Piece(PieceType::KNIGHT, Color::BLACK));
    tiles[16] = new Tile(2, 0, new Piece(PieceType::BISHOP, Color::WHITE));
    tiles[23] = new Tile(2, 7, new Piece(PieceType::BISHOP, Color::BLACK));
    tiles[24] = new Tile(3, 0, new Piece(PieceType::QUEEN, Color::WHITE));
    tiles[31] = new Tile(3, 7, new Piece(PieceType::QUEEN, Color::BLACK));
    tiles[34] = new Tile(4, 2, new Piece(PieceType::PAWN, Color::BLACK));
    tiles[40] = new Tile(5, 0, new Piece(PieceType::BISHOP, Color::WHITE));
    tiles[48] = new Tile(6, 0, new Piece(PieceType::KNIGHT, Color::WHITE));
    tiles[55] = new Tile(6, 7, new Piece(PieceType::KNIGHT, Color::BLACK));
    tiles[56] = new Tile(7, 0, new Piece(PieceType::PAWN, Color::WHITE));
    tiles[63] = new Tile(7,7, new Piece(PieceType::ROOK, Color::BLACK));

}
