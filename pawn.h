#ifndef _PAWN_H_
#define _PAWN_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class Pawn : public Piece {
    bool moved;
    public:
        Pawn(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved);
        ~Pawn();
        bool getMoved();
        void setMoved(bool moved);
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
