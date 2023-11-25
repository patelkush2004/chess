#include "piece.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// defauly constructor. used for blank spaces
Piece::Piece(Board *theBoard, bool blank, int row, int col) 
    : theBoard{theBoard}, blank{blank}, row{row}, col{col} {}

Piece::Piece(Board *theBoard, string team, char symbol, int row, int col)
 : theBoard{theBoard}, team{team}, symbol{symbol}, row{row}, col{col} {}

Piece::~Piece() {}

void Piece::setRow(int row) {
    this->row = row;
}

void Piece::setCol(int col) {
    this->col = col;
}

int Piece::getRow() {
    return row;
}

int Piece::getCol() {
    return col;
}

string Piece::getTeam() {
    return team;
}

char Piece::getSymbol() {
    return symbol;
}

bool Piece::isBlank() {
    return blank;
}

void Piece::setBlank(bool blank) {
    this->blank = blank;
}

string Piece::getTeam() {
    return this->team;
}

char Piece::getSymbol() {
    return this->symbol;
}

vector<pair<int, int>> Piece::calculatePossibleMoves() {
    vector<pair<int, int>> moves;
    move.emplace_back(4,4);
}
