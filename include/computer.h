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
        vector<pair<int, int>> levelThree(Board& b);
        vector<pair<int, int>> levelFour(Board& b);
        void levelFive(Board& b);

        // Minimax functions
        int eval(Board& b, string team);
        vector<pair<pair<int, int>, pair<int, int>>>  getMoves(Board &b, string team);
        pair<vector<pair<int, int>>, int> minimax(Board &b, int depth, string maximizing_player_color, bool maximize);
};

#endif