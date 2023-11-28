#include "piece.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// defauly constructor. used for blank spaces
Piece::Piece(Board *theBoard, int x, int y, bool blank) 
    : theBoard{theBoard}, x{x}, y{y}, blank{blank} {}

Piece::Piece(Board *theBoard, string team, char symbol, int x, int y, bool blank)
 : theBoard{theBoard}, team{team}, symbol{symbol}, x{x}, y{y}, blank{blank} {}

Piece::~Piece() {
}

void Piece::setRow(int row) {
    this->y = row+1;
}

void Piece::setCol(int col) {
    this->x = col;
}

int Piece::getRow() {
    return y-1;
}

int Piece::getCol() {
    return x;
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


vector<pair<int, int>> Piece::calculatePossibleMoves() {
    vector<pair<int, int>> moves;
    return moves;
}

Board *Piece::getBoard() {
    return theBoard;
}
