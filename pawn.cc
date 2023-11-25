#include "pawn.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(Board *theBoard, string team, char symbol, int row, int col, bool moved)
    : Piece{board, team, symbol, row, col, }, moved{moved} {}

~Pawn() {
    delete Pawn;
}

bool Pawn::getMoved() {
    return moved;
}

void Pawn::setMoved(bool moved) {
    this->moved = moved;
}

vector<pair<int, int>> Pawn::calculatePossibleMoves() {
    vector<pair<int, int>> moves;
    moves.emplace_back(4,4);
}
