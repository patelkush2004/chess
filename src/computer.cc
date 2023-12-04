#include "computer.h"
#include "player.h"
#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include "tools.h"

using namespace std;

Computer::Computer(string team, bool isCpu, bool myTurn) : 
    Player(team, isCpu, myTurn) {}

Computer::~Computer() {}

pair<int, int> Computer::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int y = letter - 'a'; 
    int x = number - '1';

    return make_pair(x, y);
}


vector<pair<int, int>> Computer::makeComputerMove(Board& b)  {

    int randomIndex;

    // this is a vector of pairs of <currentPosition, vectorPossibleMoves>
    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > moves;

    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (b.getPiece(x, y)->getTeam() == this->getTeam() && !b.getPiece(x, y)->isBlank()) {

                vector<pair<int, int>> possibleMoves =  b.getPiece(x, y)->calculatePossibleMoves();
                pair<int, int> current(b.getPiece(x, y)->getRow(), b.getPiece(x, y)->getCol());

                for (pair<int, int> move : possibleMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    moves.emplace_back(currentAndPossibleMove);
                }        
            }
        }
    }

    // seed-safe random move generation for availabliePieces
    randomIndex = randomGenerator(0, moves.size() - 1);

    pair<pair<int, int>, pair<int, int>> move = moves[randomIndex];

    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(move.first);
    fromToMove.emplace_back(move.second);

    return fromToMove;
}

