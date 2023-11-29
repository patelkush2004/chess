#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class Queen : public Piece {
    bool moved;
    public:
        Queen(Board *theBoard, string team, char symbol, int row, int col, bool blank);
        ~Queen();
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
