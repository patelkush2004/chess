#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class Bishop : public Piece {
    public:
        Bishop(Board *theBoard, string team, char symbol, int row, int col, bool blank);
        ~Bishop();
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
