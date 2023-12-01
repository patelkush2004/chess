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

    // do NOT ever use Piece by value, this causes seg faults. Use pointer to Piece instead.
    vector<Piece*> availablePieces;
    vector<pair<int, int>> moves;
    int randomIndex;
    Piece *selectedPiece = nullptr;
    
    while (true) {
        // finds all available team pieces 
        // Nit: this should be handled by board or a vector in player!
        for(int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (b.getPiece(x, y)->getTeam() == this->getTeam() && !b.getPiece(x, y)->isBlank()) {
                    availablePieces.emplace_back(b.getPiece(x, y));
                }
            }
        } // this is working perfectly, traverses through each row. 

        // seed-safe random index generation for availabliePieces
        randomIndex = randomGenerator(0, availablePieces.size() - 1);

        selectedPiece = availablePieces[randomIndex];
        //selectedPiece = b.getPiece(6,1);

        moves = selectedPiece->calculatePossibleMoves();

        // this checks if the piece has any possible moves, if not, it will clear the availablePieces vector and moves vector and try again
        if (moves.size() == 0) {
            availablePieces.clear();
            moves.clear();
            continue;
        };

        break;
    }

    // seed-safe random move generation for availabliePieces
    randomIndex = randomGenerator(0, moves.size() - 1);

    pair<int, int> move = moves[randomIndex];
    pair<int, int> current(selectedPiece->getRow(), selectedPiece->getCol());

    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(current);
    fromToMove.emplace_back(move);

    return fromToMove;
}


//vector<pair<int, int>> Computer::levelOne(Board& b) {
//}
