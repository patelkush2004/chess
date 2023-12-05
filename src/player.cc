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

// copy constructor
Player::Player(const Player &other) : 
    team{other.team}, score{other.score}, isCpu{other.isCpu}, myTurn{other.myTurn} {
}

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

void Player::setScore(int score) {
    this->score = score;
}

void Player::setMyTurn(bool turn) {
    this->myTurn = turn;
}

//void Player::setIsCpu(bool cpu) {
    //this->isCpu = cpu;
//}


void Player::setCheck(bool check) {
    this->isCheck = check;
}

bool Player::getIsCheck() {
    return isCheck;
}

void Player::setCheckmate(bool checkmate) {
    this->isCheckmate = checkmate;
}

bool Player::getIsCheckmate() {
    return isCheckmate;
}

void Player::setStalemate(bool stalemate) {
    this->isStalemate = stalemate;
}

bool Player::getIsStalemate() {
    return isStalemate;
}

void Player::setCurrentCoord(pair<int, int> coords) {
    this->currentCoord = coords;
}

void Player::setNewCoord(pair<int, int> coords) {
    this->newCoord = coords;
}

pair<int, int> Player::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int col = letter - 'a'; 
    int row = 7 - (number - '1');

    return make_pair(row, col);
}

vector<pair<int, int>> Player::makeMove(string current, string newCoord) {
    return vector<pair<int, int>>();
}
