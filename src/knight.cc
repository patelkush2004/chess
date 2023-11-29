#include "knight.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Knight::Knight(Board *theBoard, string team, char symbol, int row, int col, bool blank)
    : Piece{theBoard, team, symbol, row, col, blank} {}

Knight::~Knight() {
}

vector<pair<int, int>> Knight::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    int y = getRow();
    int x = getCol();

    // check up and to the right, stop at edges of board or when you hit a piece of the same team. capture the piece if it's the other team's
    if ((y-2 >= 0) && (x+1 < 8)) {
        if (this->getBoard()->getPiece(y-2, x+1)->isBlank()) {
            moves.emplace_back(make_pair(x+1, y-2));
        } else if (this->getBoard()->getPiece(y-2, x+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+1, y-2));
        }
    }

    // check up and to the left
    if ((y-2 >= 0) && (x-1 >= 0)) {
        if (this->getBoard()->getPiece(y-2, x-1)->isBlank()) {
            moves.emplace_back(make_pair(x-1, y-2));
        } else if (this->getBoard()->getPiece(y-2, x-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-1, y-2));
        }
    }

    // check down and to the right
    if ((y+2 < 8) && (x+1 < 8)) {
        if (this->getBoard()->getPiece(y+2, x+1)->isBlank()) {
            moves.emplace_back(make_pair(x+1, y+2));
        } else if (this->getBoard()->getPiece(y+2, x+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+1, y+2));
        }
    }

    // check down and to the left
    if ((y+2 < 8) && (x-1 >= 0)) {
        if (this->getBoard()->getPiece(y+2, x-1)->isBlank()) {
            moves.emplace_back(make_pair(x-1, y+2));
        } else if (this->getBoard()->getPiece(y+2, x-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-1, y+2));
        }
    }

    // check left and up
    if ((y-1 >= 0) && (x-2 >= 0)) {
        if (this->getBoard()->getPiece(y-1, x-2)->isBlank()) {
            moves.emplace_back(make_pair(x-2, y-1));
        } else if (this->getBoard()->getPiece(y-1, x-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-2, y-1));
        }
    }

    // check left and down
    if ((y+1 < 8) && (x-2 >= 0)) {
        if (this->getBoard()->getPiece(y+1, x-2)->isBlank()) {
            moves.emplace_back(make_pair(x-2, y+1));
        } else if (this->getBoard()->getPiece(y+1, x-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-2, y+1));
        }
    }

    // check right and up
    if ((y-1 >= 0) && (x+2 < 8)) {
        if (this->getBoard()->getPiece(y-1, x+2)->isBlank()) {
            moves.emplace_back(make_pair(x+2, y-1));
        } else if (this->getBoard()->getPiece(y-1, x+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+2, y-1));
        }
    }

    // check right and down
    if ((y+1 < 8) && (x+2 < 8)) {
        if (this->getBoard()->getPiece(y+1, x+2)->isBlank()) {
            moves.emplace_back(make_pair(x+2, y+1));
        } else if (this->getBoard()->getPiece(y+1, x+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+2, y+1));
        }
    }

    return moves;

}

