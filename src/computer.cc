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

    int col = letter - 'a'; 
    int row = 7 - (number - '1');

    return make_pair(row, col);
}


vector<pair<int, int>> Computer::makeComputerMove(Board& b, int level)  {

    vector<pair<int, int>> move;

    if (level == 1) {
        move = levelOne(b);
    } else if (level == 2) {
        move = levelTwo(b);
    }

    return move;
}

vector<pair<int, int>> Computer::levelOne(Board& b)  {
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

// levelTwo Computer
vector<pair<int, int>> Computer::levelTwo(Board& b)  {
    int randomIndex;

    // this is a vector of pairs of <currentPosition, vectorPossibleMoves>
    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > moves;

    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > captureMoves;

    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (b.getPiece(x, y)->getTeam() == this->getTeam() && !b.getPiece(x, y)->isBlank()) {

                vector<pair<int, int>> possibleCaptureMoves = b.getPiece(x, y)->capturingMoves();
                vector<pair<int, int>> possibleMoves =  b.getPiece(x, y)->calculatePossibleMoves();

                pair<int, int> current(b.getPiece(x, y)->getRow(), b.getPiece(x, y)->getCol());

                for (pair<int, int> move : possibleCaptureMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    captureMoves.emplace_back(currentAndPossibleMove);
                    cout << move.first << ", " << move.second << endl;
                }

                for (pair<int, int> move : possibleMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    moves.emplace_back(currentAndPossibleMove);
                }

            }
        }
    }

    pair<pair<int, int>, pair<int, int>> move;

    if (captureMoves.size() != 0) {
        // seed-safe random move generation for availabliePieces
        randomIndex = randomGenerator(0, captureMoves.size() - 1);
        move = captureMoves[randomIndex];
    } else if (moves.size() != 0) {
        randomIndex = randomGenerator(0, moves.size() - 1);
        move = moves[randomIndex];
    }

    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(move.first);
    fromToMove.emplace_back(move.second);

    return fromToMove;
}
