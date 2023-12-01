#include "player.h"
#include "board.h"
#include <string>
#include <vector>

using namespace std;

// Constructor
Player::Player(string team, bool isCpu, bool myTurn) : 
    team{team}, score{0} , isCpu{isCpu} , myTurn{myTurn} {
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
