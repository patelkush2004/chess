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
    bool isCheck;
    bool isCheckmate;
    bool isStalemate;
    pair<int, int> currentCoord; // current coordinate of the piece player is trying to move
    pair<int, int> newCoord; // new coordinate of the piece player is trying to move

    public:
        Player(string team, bool isCpu, bool myTurn);
        virtual ~Player();
        Player(const Player &other);
        string getTeam();
        int getScore();
        bool getIsCpu();
        bool getMyTurn();
        bool getIsCheck();
        bool getIsCheckmate();
        bool getIsStalemate();
        void setCheck(bool check);
        void setCheckmate(bool checkmate);
        void setStalemate(bool stalemate);
        pair<int, int> getCurrentCoord();
        pair<int, int> getNewCoord();
        void updateScore();
        void setScore(int score);
        //void setIsCpu(bool isCpu);
        void setMyTurn(bool myTurn);
        void setCurrentCoord(pair<int, int> currentCoord);
        void setNewCoord(pair<int, int> newCoord);
        pair<int, int> convertToCoord(string notation);
        virtual vector<pair<int, int>> makeMove(string current, string newCoord);
        virtual vector<pair<int, int>> makeComputerMove(Board& b, int level) = 0;

};

#endif
