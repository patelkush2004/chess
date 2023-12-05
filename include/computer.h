#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <string>
#include <vector>

#include "player.h"
#include "board.h"

using namespace std;

class Computer : public Player {
    public:
        Computer(string team, bool isCpu, bool myTurn);
        ~Computer();
        pair<int, int> convertToCoord(string notation);
        vector<pair<int, int>> makeComputerMove(Board& b, int level) override;
        vector<pair<int, int>> levelOne(Board& b);
        vector<pair<int, int>> levelTwo(Board& b);
};

#endif
