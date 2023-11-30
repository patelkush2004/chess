#include "bishop.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Bishop::Bishop(Board *theBoard, string team, char symbol, int row, int col, bool blank)
    : Piece{theBoard, team, symbol, row, col, blank} {}

Bishop::~Bishop() {
}

vector<pair<int, int>> Bishop::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    int y = getRow();
    int x = getCol();

    // check up and to the right, stop at edges of board or when you hit a piece of the same team. capture the piece if it's the other team's
    for (int i = 1; i < 8; ++i) {
        if ((y-i >= 0) && (x+i < 8)) {
            if (this->getBoard()->getPiece(y-i, x+i)->isBlank()) {
                moves.emplace_back(make_pair(x+i, y-i));
            } else if (this->getBoard()->getPiece(y-i, x+i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(x+i, y-i));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    // check up and to the left
    for (int i = 1; i < 8; ++i) {
        if ((y-i) >= 0 && (x-i >= 0)) {
            if (this->getBoard()->getPiece(y-i, x-i)->isBlank()) {
                moves.emplace_back(make_pair(x-i, y-i));
            } else if (this->getBoard()->getPiece(y-i, x-i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(x-i, y-i));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    // check down and to the right
    for (int i = 1; i < 8; ++i) {
        if ((y+i < 8) && (x+i < 8)) {
            if (this->getBoard()->getPiece(y+i, x+i)->isBlank()) {
                moves.emplace_back(make_pair(x+i, y+i));
            } else if (this->getBoard()->getPiece(y+i, x+i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(x+i, y+i));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    // check down and to the left
    for (int i = 1; i < 8; ++i) {
        if ((y+i < 8) && (x-i >= 0)) {
            if (this->getBoard()->getPiece(y+i, x-i)->isBlank()) {
                moves.emplace_back(make_pair(x-i, y+i));
            } else if (this->getBoard()->getPiece(y+i, x-i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(x-i, y+i));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    for (auto move : moves) {
        int temp = move.first;
        move.first = move.second;
        move.second = temp;
    }

    return moves;
}
