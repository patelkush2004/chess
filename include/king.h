#ifndef _KING_H_
#define _KING_H_

#include "piece.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;

class King : public Piece {
    bool moved;
    public:
        King(Board *theBoard, string team, char symbol, int row, int col, bool blank, bool moved);
        ~King();
        bool getMoved();
        void setMoved(bool moved);
        vector<pair<int, int>> calculatePossibleMoves() override;
};

#endif
