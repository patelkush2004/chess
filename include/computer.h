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
        vector<pair<int, int>> makeComputerMove(Board& b) override;
        vector<pair<int, int>> levelOne(Board& b);
};

#endif
