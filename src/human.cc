#include "human.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Human::Human(string team) : Player(team) {}

Human::~Human() {}

pair<int, int> Human::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int y = letter - 'a'; 
    int x = number - '1';

    return make_pair(x, y);
}

vector<pair<int, int>> Human::makeMove(string current, string newCoordString)  {
    pair<int, int> currentCoord = convertToCoord(current);
    pair<int, int> newCoord = convertToCoord(newCoordString);
    vector<pair<int, int>> move;
    move.emplace_back(currentCoord);
    move.emplace_back(newCoord);
    return move;
}
