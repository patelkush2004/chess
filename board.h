#ifndef _BOARD_H_   
#define _BOARD_H_

#include <vector>
#include <string>

#include "piece.h"
#include "player.h"
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"

class Piece;

using namespace std;

class Board : public Subject {
    vector <vector<Piece*>> theBoard; // The actual board. is a vector of vectors of pieces
    vector<Observer*> observers; // The observers of the board
    Player *p1; // The white player
    Player *p2; // The black player
    TextDisplay *td; // The text display


    public:
        Board(Player *p1, Player *p2); // Default constructor
        ~Board(); // Destructor

        void init(); // Initializes the board
        Piece *getPiece(int row, int col); // Returns the piece at the given row and column
        void setPiece(int row, int col, Piece *p); // Sets the piece at the given row and column

        void changeTurn(); // Changes the turn
        Player *getTurn(); // Gets the player whose turn it is

        void isChecked(); // Checks if the current player is in check
        void isCheckmated(); // Checks if the current player is in checkmate
        void isStalemated(); // Checks if the current player is in stalemate

        void attach(Observer *o); // Attaches an observer   
        // void detach(Observer *o); // Detaches an observer. Don't think we need this
        void notifyObservers() override; // Notifies all observers

        friend ostream &operator<<(ostream &out, const Board &b); // Overloaded output operator
};

#endif
