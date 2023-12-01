#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>

class Board;

using namespace std;

class Player {
    string team; // white or black
    int score; // score of the player
    bool isCpu; // true if the player is a cpu
    bool myTurn; // true if it is the player's turn
    pair<int, int> currentCoord; // current coordinate of the piece player is trying to move
    pair<int, int> newCoord; // new coordinate of the piece player is trying to move

    public:
        Player(string team);
        virtual ~Player();
        string getTeam();
        int getScore();
        bool getIsCpu();
        bool getMyTurn();
        pair<int, int> getCurrentCoord();
        pair<int, int> getNewCoord();
        void updateScore();
        //void setIsCpu(bool isCpu);
        void setMyTurn(bool myTurn);
        void setCurrentCoord(pair<int, int> currentCoord);
        void setNewCoord(pair<int, int> newCoord);
        pair<int, int> convertToCoord(string notation);
        virtual vector<pair<int, int>> makeMove(string current, string newCoord);
        virtual vector<pair<int, int>> makeComputerMove(Board& b) = 0;

};

#endif
