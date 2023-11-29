#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class Rook : public Piece {
    bool moved;
    public:
        Rook(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved);
        ~Rook();
        bool getMoved();
        void setMoved(bool moved);
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
