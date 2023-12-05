#ifndef _HUMAN_H_
#define _HUMAN_H_

#include <string>
#include <vector>

#include "player.h"

using namespace std;

class Human : public Player {
    public:
        Human(string team, bool isCpu, bool myTurn);
        ~Human();
        pair<int, int> convertToCoord(string notation);
        vector<pair<int, int>> makeMove(string current, string newCoord) override;
        vector<pair<int, int>> makeComputerMove(Board& b, int level) override;
};

#endif