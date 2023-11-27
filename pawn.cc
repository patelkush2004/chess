#include "pawn.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved)
    : Piece{theBoard, team, symbol, row, col, blank}, moved{moved} {}

Pawn::~Pawn() {
}

bool Pawn::getMoved() {
    return moved;
}

void Pawn::setMoved(bool moved) {
    this->moved = moved;
}

vector<pair<int, int>> Pawn::calculatePossibleMoves() {
    vector<pair<int, int>> moves;

    /*
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; i < 8; ++j) {
            moves.emplace_back(i, j);
        }
    }
    */

    moves.emplace_back(4,4);
    return moves;
}
