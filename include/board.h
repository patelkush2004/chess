#ifndef _BOARD_H_   
#define _BOARD_H_

#include <vector>
#include <string>
#include <stack>

#include "piece.h"
#include "player.h"
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"
#include "graphicdisplay.h"

class Piece;

using namespace std;

class Board : public Subject {
    vector<vector<Piece*>> theBoard; // The actual board. is a vector of vectors of pieces
    stack<vector<vector<string>>> boardStates; // boardStates, a stack of board states

    vector<Observer*> observers; // The observers of the board
    Player *p1; // The white player
    Player *p2; // The black player
    TextDisplay *td; // The text display
    GraphicDisplay *gd; // The graphic display

    public:
        Board(Player *p1, Player *p2); // Default constructor
        ~Board(); // Destructor
        Board(const Board &other); // Copy constructor

        pair<int,int> gdCurrentCoord; // old coordinate for the graphicdisplay
        pair<int,int> gdNewCoord; // new coordinate for the graphicdisplay

        void init(); // Initializes the board
        void setup(); // Puts the board in setup mode
        Piece *getPiece(int row, int col); // Returns the piece at the given row and column
        void setPiece(int row, int col, Piece *p); // Sets the piece at the given row and column

        GraphicDisplay* getGd() { return gd; }

        void changeTurn(); // Changes the turn
        Player *getTurn(); // Gets the player whose turn it is

        void movePiece(vector<pair<int, int>> move); // Moves the piece

        Player* getP1();
        Player* getP2();

        void clearBoard(); // Clears the board
        void clearBoardStates(); // Clears the board states

        void isChecked(); // Checks if the current player is in check
        void isCheckmated(); // Checks if the current player is in checkmate
        void isStalemated(); // Checks if the current player is in stalemate
        void reversePiece();

        void boardtoState(); // Converts the board to a state
        void applyState(vector<vector<string>> state); // Applies the given state to the board

        void attach(Observer *o); // Attaches an observer   
        // void detach(Observer *o); // Detaches an observer. Don't think we need this
        void notifyObservers() override; // Notifies all observers
        void notifyGraphicObservers();

        friend ostream &operator<<(ostream &out, const Board &b); // Overloaded output operator

        string arrayToFENSyntax(Board& b);


};

#endif
