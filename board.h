#ifndef _BOARD_H_   
#define _BOARD_H_

#include <vector>
#include <string>

#include "piece.h"
#include "player.h"
#include "subject.h"

class Board : public Subject {
    vector <vector<Piece*>> theBoard; // The actual board. is a vector of vectors of pieces
    Player *whitePlayer; // The white player
    Player *blackPlayer; // The black player

    public:
        Board(); // Default constructor
        ~Board(); // Destructor

        void init(); // Initializes the board
        Piece *getPiece(int row, int col); // Returns the piece at the given row and column
        void setPiece(int row, int col, Piece *p); // Sets the piece at the given row and column

        void changeTurn(); // Changes the turn
        void getTurn(); // Gets the turn

        void isChedked(); // Checks if the current player is in check
        void isCheckmated(); // Checks if the current player is in checkmate

        void attach(Observer *o); // Attaches an observer   
        void detach(Observer *o); // Detaches an observer
        void notifyObservers(); // Notifies all observers

}
