#include "computer.h"
#include "player.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>
#include "tools.h"

using namespace std;

Computer::Computer(string team) : Player(team) {}

Computer::~Computer() {}

pair<int, int> Computer::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int y = letter - 'a'; 
    int x = number - '1';

    return make_pair(x, y);
}


vector<pair<int, int>> Computer::makeComputerMove(Board& b)  {
    vector<pair<int, int>> move = levelOne(b);
    return move;
}


vector<pair<int, int>> Computer::levelOne(Board& b) {

    vector<Piece> availablePieces;
    
    // finds all available team pieces 
    // Nit: this should be handled by board or a vector in player!
    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (b.getPiece(x, y)->getTeam() == this->getTeam()) {
                availablePieces.emplace_back(*b.getPiece(x, y));
            }
        }
    }

    // seed-safe random index generation for availabliePieces
    int randomIndex = randomGenerator(0, availablePieces.size() - 1);

    Piece selectedPiece = availablePieces[randomIndex];

    std::vector<std::pair<int, int>> moves = selectedPiece.calculatePossibleMoves();

    // seed-safe random move generation for availabliePieces
    randomIndex = randomGenerator(0, moves.size() - 1);

    pair<int, int> move = moves[randomIndex];

    pair<int, int> current(selectedPiece.getCol(), selectedPiece.getRow());
    
    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(current);
    fromToMove.emplace_back(move);

    return fromToMove;
}
