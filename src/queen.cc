#include "queen.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Queen::Queen(Board *theBoard, string team, char symbol, int row, int col, bool blank)
    : Piece{theBoard, team, symbol, row, col, blank} {}

Queen::~Queen() {
}

vector<pair<int, int>> Queen::calculatePossibleMoves() {
    // combine the possible moves of a rook and bishop
    vector<pair<int, int>> moves;

    int row = getRow();
    int col = getCol();

    /* ROOK MOVES */
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

    /* BISHOP MOVES */
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
