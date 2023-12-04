#include "pawn.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved)
    : Piece{theBoard, team, symbol, row, col, blank}, moved{moved} {}

Pawn::~Pawn() {
}

bool Pawn::getMoved() {
    return moved;
}

void Pawn::setMoved(bool moved) {
    this->moved = moved;
}

vector<pair<int, int>> Pawn::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    int row = getRow();
    int col = getCol();
    bool moved = getMoved();

    if (!moved) { // if the pawn hasn't moved yet, it can move 2 spaces
        if (getTeam() == "white") {
            // white pawns move up the board which is down the vector
            if (row > 0 && this->getBoard()->getPiece(row-1, col)->isBlank()) {
                moves.emplace_back(make_pair(row-1, col)); 
            }
            if (row > 1 && this->getBoard()->getPiece(row-2, col)->isBlank()) {
                moves.emplace_back(make_pair(row-2, col));
            }
        } else {
            // black pawns move down the board which is up the vector
            if (row < 7 && this->getBoard()->getPiece(row+1, col)->isBlank()) {
                moves.emplace_back(make_pair(row+1, col));
            }
            if (row < 6 && this->getBoard()->getPiece(row+2, col)->isBlank()) {
                moves.emplace_back(make_pair(row+2, col));
            }
        }
    } else {
        if (getTeam() == "white") {
            // white pawns move up the board which is down the vector
            if (row > 0 && this->getBoard()->getPiece(row-1, col)->isBlank()) {
                moves.emplace_back(make_pair(row-1, col)); 
            }
        } else {
            // black pawns move down the board which is up the vector
            if (row < 7 && this->getBoard()->getPiece(row+1, col)->isBlank()) {
                moves.emplace_back(make_pair(row+1, col));
            }
        }
    }

    // attacking opponent's piece
    if ((getTeam() == "white") && (row != 0) && (col != 0)) {
        if (this->getBoard()->getPiece(row-1, col-1)->getTeam() == "black") {
            // white pawns move up the board which is down the vector
            moves.emplace_back(make_pair(row-1, col-1));
        }
    } 
    if ((getTeam() == "white") && (row != 0) && (col != 7)) {
        if (this->getBoard()->getPiece(row - 1, col+1)->getTeam() == "black") {
            // white pawns move up the board which is down the vector
            moves.emplace_back(make_pair(row-1, col + 1));
        }
    }

    // attacking opponent's piece
    if ((getTeam() == "black") && (row != 7) && (col != 0)) {
        if (this->getBoard()->getPiece(row+1, col-1)->getTeam() == "white") {
            // black pawns move down the board which is up the vector
            moves.emplace_back(make_pair(row+1, col-1));
        }
    }
    if ((getTeam() == "black") && (row != 7) && (col != 7)) {
        if (this->getBoard()->getPiece(row + 1, col+1)->getTeam() == "white") {
            // black pawns move down the board which is up the vector
            moves.emplace_back(make_pair(row + 1, col + 1));
        }
    }

    return moves;
}

