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

    int row = getRow();
    int col = getCol();

    // move up until a piece is encountered or the edge of the board is reached or 
    // an opponent's piece is encountered
    for (int i = 1; i < 8; ++i) {
        if (row-i >= 0) {
            if (this->getBoard()->getPiece(row-i, col)->isBlank()) {
                moves.emplace_back(make_pair(row-i, col));
            } 
            else if (this->getBoard()->getPiece(row-i, col)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(row-i, col));
                break;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    // move down until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = 1; i < 8; ++i) {
        if (row+i < 8) {
            if (this->getBoard()->getPiece(row+i, col)->isBlank()) {
                moves.emplace_back(make_pair(row+i, col));
            } 
            else if (this->getBoard()->getPiece(row+i, col)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(row+i, col));
                break;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    // move left until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = 1; i < 8; ++i) {
        if (col-i >= 0) {
            if (this->getBoard()->getPiece(row, col-i)->isBlank()) {
                moves.emplace_back(make_pair(row, col-i));
            } 
            else if (this->getBoard()->getPiece(row, col-i)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(row, col-i));
                break;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    // move right until a piece is encountered or the edge of the board is reached or an opponent's piece is encountered
    for (int i = 1; i < 8; ++i) {
        if (col+i < 8) {
            if (this->getBoard()->getPiece(row, col+i)->isBlank()) {
                moves.emplace_back(make_pair(row, col+i));
            } 
            else if (this->getBoard()->getPiece(row, col+i)->getTeam() != getTeam()) {
                moves.emplace_back(make_pair(row, col+i));
                break;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    return moves;
}
