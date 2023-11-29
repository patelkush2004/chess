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

    int y = getRow();
    int x = getCol();
    bool moved = getMoved(); // not used yet. used for castling

    // check if the king can move up
    if (y > 0) {
        if (this->getBoard()->getPiece(y-1, x)->isBlank()) {
            moves.emplace_back(make_pair(x, y-1));
        } else if (this->getBoard()->getPiece(y-1, x)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x, y-1));
        }
    }

    // check if the king can move down
    if (y < 7) {
        if (this->getBoard()->getPiece(y+1, x)->isBlank()) {
            moves.emplace_back(make_pair(x, y+1));
        } else if (this->getBoard()->getPiece(y+1, x)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x, y+1));
        }
    }

    // check if the king can move left
    if (x > 0) {
        if (this->getBoard()->getPiece(y, x-1)->isBlank()) {
            moves.emplace_back(make_pair(x-1, y));
        } else if (this->getBoard()->getPiece(y, x-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-1, y));
        }
    }

    // check if the king can move right
    if (x < 7) {
        if (this->getBoard()->getPiece(y, x+1)->isBlank()) {
            moves.emplace_back(make_pair(x+1, y));
        } else if (this->getBoard()->getPiece(y, x+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+1, y));
        }
    }

    // check if the king can move up and left
    if ((y > 0) && (x > 0)) {
        if (this->getBoard()->getPiece(y-1, x-1)->isBlank()) {
            moves.emplace_back(make_pair(x-1, y-1));
        } else if (this->getBoard()->getPiece(y-1, x-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-1, y-1));
        }
    }

    // check if the king can move up and right 
    if ((y > 0) && (x < 7)) {
        if (this->getBoard()->getPiece(y-1, x+1)->isBlank()) {
            moves.emplace_back(make_pair(x+1, y-1));
        } else if (this->getBoard()->getPiece(y-1, x+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+1, y-1));
        }
    }

    // check if the king can move down and left
    if ((y < 7) && (x > 0)) {
        if (this->getBoard()->getPiece(y+1, x-1)->isBlank()) {
            moves.emplace_back(make_pair(x-1, y+1));
        } else if (this->getBoard()->getPiece(y+1, x-1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x-1, y+1));
        }
    }

    // check if the king can move down and right
    if ((y < 7) && (x < 7)) {
        if (this->getBoard()->getPiece(y+1, x+1)->isBlank()) {
            moves.emplace_back(make_pair(x+1, y+1));
        } else if (this->getBoard()->getPiece(y+1, x+1)->getTeam() != this->getTeam()) {
            moves.emplace_back(make_pair(x+1, y+1));
        }
    }

    return moves;
}
