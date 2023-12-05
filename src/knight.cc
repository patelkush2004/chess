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

    int row = getRow();
    int col = getCol();

    // check up and to the right, stop at edges of board or when you hit a piece of the same team. capture the piece if it's the other team's
    if ((row-2 >= 0) && (col+1 < 8)) {
        if (this->getBoard()->getPiece(row-2, col+1)->isBlank()) {
            moves.emplace_back(make_pair(row-2, col+1));
        } else if (this->getBoard()->getPiece(row-2, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-2, col+1));
        }
    }

    // check up and to the left
    if ((row-2 >= 0) && (col-1 >= 0)) {
        if (this->getBoard()->getPiece(row-2, col-1)->isBlank()) {
            moves.emplace_back(make_pair(row-2, col-1));
        } else if (this->getBoard()->getPiece(row-2, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-2, col-1));
        }
    }

    // check down and to the right
    if ((row+2 < 8) && (col+1 < 8)) {
        if (this->getBoard()->getPiece(row+2, col+1)->isBlank()) {
            moves.emplace_back(make_pair(row+2, col+1));
        } else if (this->getBoard()->getPiece(row+2, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+2, col+1));
        }
    }

    // check down and to the left
    if ((row+2 < 8) && (col-1 >= 0)) {
        if (this->getBoard()->getPiece(row+2, col-1)->isBlank()) {
            moves.emplace_back(make_pair(row+2, col-1));
        } else if (this->getBoard()->getPiece(row+2, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+2, col-1));
        }
    }

    // check left and up
    if ((row-1 >= 0) && (col-2 >= 0)) {
        if (this->getBoard()->getPiece(row-1, col-2)->isBlank()) {
            moves.emplace_back(make_pair(row-1, col-2));
        } else if (this->getBoard()->getPiece(row-1, col-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col-2));
        }
    }

    // check left and down
    if ((row+1 < 8) && (col-2 >= 0)) {
        if (this->getBoard()->getPiece(row+1, col-2)->isBlank()) {
            moves.emplace_back(make_pair(row+1, col-2));
        } else if (this->getBoard()->getPiece(row+1, col-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col-2));
        }
    }

    // check right and up
    if ((row-1 >= 0) && (col+2 < 8)) {
        if (this->getBoard()->getPiece(row-1, col+2)->isBlank()) {
            moves.emplace_back(make_pair(row-1, col+2));
        } else if (this->getBoard()->getPiece(row-1, col+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col+2));
        }
    }

    // check right and down
    if ((row+1 < 8) && (col+2 < 8)) {
        if (this->getBoard()->getPiece(row+1, col+2)->isBlank()) {
            moves.emplace_back(make_pair(row+1, col+2));
        } else if (this->getBoard()->getPiece(row+1, col+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col+2));
        }
    }

    return moves;
}

vector<pair<int, int>> Knight::capturingMoves() {
    vector<pair<int, int>> moves;

    int row = getRow();
    int col = getCol();

    // check up and to the right, stop at edges of board or when you hit a piece of the same team. capture the piece if it's the other team's
    if ((row-2 >= 0) && (col+1 < 8)) {
        if (this->getBoard()->getPiece(row-2, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-2, col+1));
        }
    }

    // check up and to the left
    if ((row-2 >= 0) && (col-1 >= 0)) {
        if (this->getBoard()->getPiece(row-2, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-2, col-1));
        }
    }

    // check down and to the right
    if ((row+2 < 8) && (col+1 < 8)) {
        if (this->getBoard()->getPiece(row+2, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+2, col+1));
        }
    }

    // check down and to the left
    if ((row+2 < 8) && (col-1 >= 0)) {
        if (this->getBoard()->getPiece(row+2, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+2, col-1));
        }
    }

    // check left and up
    if ((row-1 >= 0) && (col-2 >= 0)) {
        if (this->getBoard()->getPiece(row-1, col-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col-2));
        }
    }

    // check left and down
    if ((row+1 < 8) && (col-2 >= 0)) {
        if (this->getBoard()->getPiece(row+1, col-2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col-2));
        }
    }

    // check right and up
    if ((row-1 >= 0) && (col+2 < 8)) {
        if (this->getBoard()->getPiece(row-1, col+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col+2));
        }
    }

    // check right and down
    if ((row+1 < 8) && (col+2 < 8)) {
        if (this->getBoard()->getPiece(row+1, col+2)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col+2));
        }
    }

    return moves;
}
