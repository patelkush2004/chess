#include "king.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

King::King(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved)
    : Piece{theBoard, team, symbol, row, col, blank}, moved{moved} {}

King::~King() {
}

bool King::getMoved() {
    return moved;
}

void King::setMoved(bool moved) {
    this->moved = moved;
}

vector<pair<int, int>> King::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    int row = getRow();
    int col = getCol();

    // check if the king can move up
    if (row > 0) {
        if (this->getBoard()->getPiece(row-1, col)->isBlank()) {
            moves.emplace_back(make_pair(row-1, col));
        } else if (this->getBoard()->getPiece(row-1, col)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col));
        }
    }

    // check if the king can move down
    if (row < 7) {
        if (this->getBoard()->getPiece(row+1, col)->isBlank()) {
            moves.emplace_back(make_pair(row+1, col));
        } else if (this->getBoard()->getPiece(row+1, col)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col));
        }
    }

    // check if the king can move left
    if (col > 0) {
        if (this->getBoard()->getPiece(row, col-1)->isBlank()) {
            moves.emplace_back(make_pair(row, col-1));
        } else if (this->getBoard()->getPiece(row, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row, col-1));
        }
    }

    // check if the king can move right
    if (col < 7) {
        if (this->getBoard()->getPiece(row, col+1)->isBlank()) {
            moves.emplace_back(make_pair(row, col+1));
        } else if (this->getBoard()->getPiece(row, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row, col+1));
        }
    }

    // check if the king can move up and left
    if ((row > 0) && (col > 0)) {
        if (this->getBoard()->getPiece(row-1, col-1)->isBlank()) {
            moves.emplace_back(make_pair(row-1, col-1));
        } else if (this->getBoard()->getPiece(row-1, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col-1));
        }
    }

    // check if the king can move up and right 
    if ((row > 0) && (col < 7)) {
        if (this->getBoard()->getPiece(row-1, col+1)->isBlank()) {
            moves.emplace_back(make_pair(row-1, col+1));
        } else if (this->getBoard()->getPiece(row-1, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col+1));
        }
    }

    // check if the king can move down and left
    if ((row < 7) && (col > 0)) {
        if (this->getBoard()->getPiece(row+1, col-1)->isBlank()) {
            moves.emplace_back(make_pair(row+1, col-1));
        } else if (this->getBoard()->getPiece(row+1, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col-1));
        }
    }

    // check if the king can move down and right
    if ((row < 7) && (col < 7)) {
        if (this->getBoard()->getPiece(row+1, col+1)->isBlank()) {
            moves.emplace_back(make_pair(row+1, col+1));
        } else if (this->getBoard()->getPiece(row+1, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col+1));
        }
    }

    // castling
    
    if(this->getMoved() ==  false) {
        // check if the king can castle left
        if (this->getBoard()->getPiece(row, col-1)->isBlank() && this->getBoard()->getPiece(row, col-2)->isBlank() && this->getBoard()->getPiece(row, col-3)->isBlank()) {
                moves.emplace_back(make_pair(row, col-2));
        }

        // check if the king can castle right
        if (this->getBoard()->getPiece(row, col+1)->isBlank() && this->getBoard()->getPiece(row, col+2)->isBlank()) {
                moves.emplace_back(make_pair(row, col+2));
        }
    }

    return moves;
}

vector<pair<int, int>> King::capturingMoves() {
    vector<pair<int, int>> moves;

    int row = getRow();
    int col = getCol();

    // check if the king can move up
    if (row > 0) {
        if (this->getBoard()->getPiece(row-1, col)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col));
        }
    }

    // check if the king can move down
    if (row < 7) {
        if (this->getBoard()->getPiece(row+1, col)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col));
        }
    }

    // check if the king can move left
    if (col > 0) {
        if (this->getBoard()->getPiece(row, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row, col-1));
        }
    }

    // check if the king can move right
    if (col < 7) {
        if (this->getBoard()->getPiece(row, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row, col+1));
        }
    }

    // check if the king can move up and left
    if ((row > 0) && (col > 0)) {
        if (this->getBoard()->getPiece(row-1, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col-1));
        }
    }

    // check if the king can move up and right 
    if ((row > 0) && (col < 7)) {
        if (this->getBoard()->getPiece(row-1, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row-1, col+1));
        }
    }

    // check if the king can move down and left
    if ((row < 7) && (col > 0)) {
        if (this->getBoard()->getPiece(row+1, col-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col-1));
        }
    }

    // check if the king can move down and right
    if ((row < 7) && (col < 7)) {
        if (this->getBoard()->getPiece(row+1, col+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(row+1, col+1));
        }
    }

    return moves;
}

