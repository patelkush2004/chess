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

    int y = getRow();
    int x = getCol();
    bool moved = getMoved();

    if (!moved) { // if the pawn hasn't moved yet, it can move 2 spaces
        if (getTeam() == "white") {
            // white pawns move up the board which is down the vector
            moves.emplace_back(make_pair(x, y-1)); 
            moves.emplace_back(make_pair(x, y-2));
        } else {
            // black pawns move down the board which is up the vector
            moves.emplace_back(make_pair(x, y+1));
            moves.emplace_back(make_pair(x, y+2));
        }
        this->setMoved(true);
    } else {
        if (getTeam() == "white") {
            moves.emplace_back(make_pair(x, y-1));
        } else {
            moves.emplace_back(make_pair(x, y+1));
        }
    }


    // attacking opponent's piece
    if ((getTeam() == "white") && (x != 0) && (y != 0)) {
        if (this->getBoard()->getPiece(x - 1, y - 1)->getTeam() == "black") {
            // white pawns move up the board which is down the vector
            moves.emplace_back(make_pair(x - 1, y - 1));
        }
    } 
    if ((getTeam() == "white") && (x != 7) && (y != 0)) {
        if (this->getBoard()->getPiece(x + 1, y - 1)->getTeam() == "black") {
            // white pawns move up the board which is down the vector
            moves.emplace_back(make_pair(x + 1, y - 1));
        }
    }

    // attacking opponent's piece
    if ((getTeam() == "black") && (x != 0) && (y != 7)) {
        if (this->getBoard()->getPiece(x - 1, y + 1)->getTeam() == "white") {
            // black pawns move down the board which is up the vector
            moves.emplace_back(make_pair(x - 1, y + 1));
        }
    }
    if ((getTeam() == "black") && (x != 7) && (y != 7)) {
        if (this->getBoard()->getPiece(x + 1, y + 1)->getTeam() == "white") {
            // black pawns move down the board which is up the vector
            moves.emplace_back(make_pair(x + 1, y + 1));
        }
    }

    return moves;
}
