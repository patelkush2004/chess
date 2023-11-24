#include "board.h"

using namespace std;

// Constructor
Board::Board(Player *whitePlayer, Player *blackPlayer) : 
    whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {}

// Destructor
Board::~Board() {
    delete whitePlayer;
    delete blackPlayer;
}

// init creates the piece and places them on the board. 
// by placing them on the board, it simply sets the coordinates properly

void Board::init() {
    // White pieces
    for (int i = 0; i < 8; ++i) {
        vector<Coordinate> possibleMoves;
        pieces.emplace_back(new Pawn{possibleMoves, white, P, i, 1, false, false});
        
    }

    // Black pieces
    for (int i = 0; i < 8; ++i) {
        vector<Coordinate> possibleMoves = getPiece(i, 0)->calculatePossibleMoves();
        pieces.emplace_back(new Pawn{possibleMoves, black, P, i, 6, false, false});
    }
}