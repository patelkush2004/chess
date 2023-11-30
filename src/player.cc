#include "player.h"
#include <string>
#include <vector>

using namespace std;

// Constructor
Player::Player(string team) : 
    team{team} {
        if (team == "white" || team == "White") {
            this->myTurn = true;
        }
        else {
            this->myTurn = false;
        }
        currentCoord = {0,0};
        newCoord = {0,0};
        score = 0;
        isCpu = false;
}

// Destructor
Player::~Player() {}

// Getters
string Player::getTeam() {
    return team;
}

int Player::getScore() {
    return score;
}

bool Player::getMyTurn() {
    return myTurn;
}

bool Player::getIsCpu() {
    return isCpu;
}

pair<int, int> Player::getCurrentCoord() {
    return currentCoord;
}

pair<int, int> Player::getNewCoord() {
    return newCoord;
}

// Setters
void Player::updateScore() {
    this->score++;
}

void Player::setMyTurn(bool turn) {
    this->myTurn = turn;
}

//void Player::setIsCpu(bool cpu) {
    //this->isCpu = cpu;
//}

void Player::setCurrentCoord(pair<int, int> coords) {
    this->currentCoord = coords;
}

void Player::setNewCoord(pair<int, int> coords) {
    this->newCoord = coords;
}
pair<int, int> Player::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int y = letter - 'a'; 
    int x = number - '1';

    return make_pair(x, y);
}

vector<pair<int, int>> Player::makeMove(string current, string newCoord) {
    return vector<pair<int, int>>();
}

