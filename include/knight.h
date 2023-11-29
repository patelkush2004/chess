#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class Knight : public Piece {
    public:
        Knight(Board *theBoard, string team, char symbol, int row, int col, bool blank);
        ~Knight();
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
