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

    int row = getRow();
    int col = getCol();

    // check up and to the right, 
    // stop at edges of board or when rowou hit a piece of the same team. 
    // capture the piece if it's the other team's
    for (int i = 1; i < 8; ++i) {
        if ((row-i >= 0) && (col+i < 8)) {
            if (this->getBoard()->getPiece(row-i, col+i)->isBlank()) {
                moves.emplace_back(make_pair(row-i, col+i));
            } else if (this->getBoard()->getPiece(row-i, col+i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(row-i, col+i));
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
        if ((row-i) >= 0 && (col-i >= 0)) {
            if (this->getBoard()->getPiece(row-i, col-i)->isBlank()) {
                moves.emplace_back(make_pair(row-i, col-i));
            } else if (this->getBoard()->getPiece(row-i, col-i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(row-i, col-i));
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
        if ((row+i < 8) && (col+i < 8)) {
            if (this->getBoard()->getPiece(row+i, col+i)->isBlank()) {
                moves.emplace_back(make_pair(row+i, col+i));
            } else if (this->getBoard()->getPiece(row+i, col+i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(row+i, col+i));
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
        if ((row+i < 8) && (col-i >= 0)) {
            if (this->getBoard()->getPiece(row+i, col-i)->isBlank()) {
                moves.emplace_back(make_pair(row+i, col-i));
            } else if (this->getBoard()->getPiece(row+i, col-i)->getTeam() != this->getTeam()) {
                moves.emplace_back(make_pair(row+i, col-i));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    return moves;
}
