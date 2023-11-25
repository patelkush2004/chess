#include "player.h"

using namespace std;

// Constructor
Player::Player(string team) : 
    team{team} {
        if (team = "white" || team == "White") {
            this->myTurn = true;
        }
        else {
            this->myTurn = false;
        }
        currentCoords;
        newCoords;
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

bool Player::getTurn() {
    return myTurn;
}

bool Player::getIsCpu() {
    return isCpu;
}

vector<int> Player::getCurrentCoords() {
    return currentCoords;
}

vector<int> Player::getNewCoords() {
    return newCoords;
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

void Player::setCurrentCoords(vector<int> coords) {
    this->currentCoords = coords;
}

void Player::setNewCoords(vector<int> coords) {
    this->newCoords = coords;
}

vector<pair<int, int>> Player::makeMove() {
    vector<pair<int, int>> move;
    move.emplace_back(this->currentCoords); 
    move.emplace_back(this->newCoords);
    return move;
}
