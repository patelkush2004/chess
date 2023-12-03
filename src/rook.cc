#include "rook.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Rook::Rook(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved)
    : Piece{theBoard, team, symbol, row, col, blank}, moved{moved} {}

Rook::~Rook() {
}

bool Rook::getMoved() {
    return moved;
}

void Rook::setMoved(bool moved) {
    this->moved = moved;
}

vector<pair<int, int>> Rook::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    int y = getRow();
    int x = getCol();
    bool moved = getMoved();

    // move up until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = y-1; i >= 0; --i) {
        if (this->getBoard()->getPiece(i, x)->isBlank()) {
            moves.emplace_back(make_pair(x, i));
        } else {
            if (this->getBoard()->getPiece(i, x)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(x, i));
            }
            break;
        }
    }

    // move down until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = y+1; i < 8; ++i) {
        if (this->getBoard()->getPiece(i, x)->isBlank()) {
            moves.emplace_back(make_pair(x, i));
        } else {
            if (this->getBoard()->getPiece(i, x)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(x, i));
            }
            break;
        }
    }

    // move left until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = x-1; i >= 0; --i) {
        if (this->getBoard()->getPiece(y, i)->isBlank()) {
            moves.emplace_back(make_pair(i, y));
        } else {
            if (this->getBoard()->getPiece(y, i)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(i, y));
            }
            break;
        }
    }

    // move right until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = x+1; i < 8; ++i) {
        if (this->getBoard()->getPiece(y, i)->isBlank()) {
            moves.emplace_back(make_pair(i, y));
        } else {
            if (this->getBoard()->getPiece(y, i)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(i, y));
            }
            break;
        }
    }

   for (auto &move : moves) {
        int temp = move.first;
        move.first = move.second;
        move.second = temp;
    }

    return moves;

}
