#include "human.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Human::Human(string team, bool isCpu, bool myTurn) : 
    Player(team, isCpu, myTurn) {}

Human::~Human() {}

pair<int, int> Human::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int col = letter - 'a'; 
    int row = 7 - (number - '1');

    return make_pair(row, col);
}

vector<pair<int, int>> Human::makeMove(string current, string newCoordString)  {
    pair<int, int> currentCoord = convertToCoord(current);
    pair<int, int> newCoord = convertToCoord(newCoordString);
    vector<pair<int, int>> move;
    move.emplace_back(currentCoord);
    move.emplace_back(newCoord);
    return move;
}

vector<pair<int, int>> Human::makeComputerMove(Board& b)  {
    return vector<pair<int, int>>();
}

