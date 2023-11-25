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

vector<pair<int, int>> Player::makeMove() {
    vector<pair<int, int>> move;
    move.push_back(this->currentCoord); 
    move.push_back(this->newCoord);
    return move;
}

