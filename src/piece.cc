#include "piece.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// defauly constructor. used for blank spaces
Piece::Piece(Board *theBoard, int row, int col, bool blank) 
    : theBoard{theBoard}, row{row}, col{col}, blank{blank} {}

Piece::Piece(Board *theBoard, string team, char symbol, int row, int col, bool blank)
 : theBoard{theBoard}, team{team}, symbol{symbol}, row{row}, col{col}, blank{blank} {}

Piece::~Piece() {
}

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


vector<pair<int, int>> Piece::calculatePossibleMoves() {
    vector<pair<int, int>> moves;
    return moves;
}

vector<pair<int, int>> Piece::capturingMoves() {
    vector<pair<int, int>> moves;
    return moves;
}

Board *Piece::getBoard() {
    return theBoard;
}
