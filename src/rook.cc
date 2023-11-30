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

    /*

    // if the rook hasn't moved yet, check if it can castle
    if (!moved) {
        // check if the king is in check

        // check if the squares between the rook and king are blank
        if (this->getBoard()->getPiece(y, x+1)->isBlank() && this->getBoard()->getPiece(y, x+2)->isBlank()) {
            if (this->getBoard()->getPiece(y, x+3)->getSymbol() == 'K') {
                if (this->getBoard()->getPiece(y, x+3)->getTeam() == getTeam()) {
                    if (!this->getBoard()->getPiece(y, x+3)->getMoved()) { // check if the king has moved
                        moves.emplace_back(make_pair(x+2, y));
                    }
                }
            }
        }

        // check if the squares between the rook and king are blank
        if (this->getBoard()->getPiece(y, x-1)->isBlank() && this->getBoard()->getPiece(y, x-2)->isBlank() && this->getBoard()->getPiece(y, x-3)->isBlank()) {
            if (this->getBoard()->getPiece(y, x-4)->getSymbol() == 'K') {
                if (this->getBoard()->getPiece(y, x-4)->getTeam() == getTeam()) {
                    if (!this->getBoard()->getPiece(y, x-4)->getMoved()) { // check if the king has moved
                        moves.emplace_back(make_pair(x-2, y));
                    }
                }
            }
        }
    }

    */

   for (auto &move : moves) {
        int temp = move.first;
        move.first = move.second;
        move.second = temp;
    }

    return moves;

}
