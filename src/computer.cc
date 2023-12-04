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


vector<pair<int, int>> Computer::makeComputerMove(Board& b)  {

    vector<Piece*> availablePieces;
    vector<pair<int, int>> moves;
    int randomIndex;
    Piece *selectedPiece = nullptr;
    
    while (true) {
        // finds all available team pieces 
        // Nit: this should be handled by board or a vector in player!
        for(int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (b.getPiece(row, col)->getTeam() == this->getTeam() && !b.getPiece(row, col)->isBlank()) {
                    availablePieces.emplace_back(b.getPiece(row, col));
                }
            }
        } 

        // seed-safe random index generation for availabliePieces
        randomIndex = randomGenerator(0, availablePieces.size() - 1);

        selectedPiece = availablePieces[randomIndex];

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

    availablePieces.clear();
    moves.clear();

    return fromToMove;
}


//vector<pair<int, int>> Computer::levelOne(Board& b) {
//}
