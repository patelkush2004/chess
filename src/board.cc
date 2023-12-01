#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

// Constructor
Board::Board(Player *p1, Player *p2) : 
    p1{p1}, p2{p2} {
        //vector <vector<Piece*>> theBoard = {};
        this->td = nullptr;
        this->gd = nullptr;
    }

// Destructor
Board::~Board() {
    for (auto &p : theBoard) {
        for (auto &piece : p) {
            delete piece;
        }
    }
    if (td != nullptr) {
        delete td;
    } 

    //if (gd != nullptr) {
        //delete gd;
    //}
}

// init creates the piece and places them on the board. 
// by placing them on the board, it simply sets the coordinates properly

void Board::init() {
    td = new TextDisplay();
    //gd = new GraphicDisplay();

    vector<Piece*> row;

    // top row of the board. for the sake of pawn testing. leave it blank
    row.emplace_back(new Rook(this, "black", 'r', 0, 0, false, false));
    row.emplace_back(new Knight(this, "black", 'n', 1, 0, false));
    row.emplace_back(new Bishop(this, "black", 'b', 2, 0, false));
    row.emplace_back(new Queen(this, "black", 'q', 3, 0, false));
    row.emplace_back(new King(this, "black", 'k', 4, 0, false, false));
    row.emplace_back(new Bishop(this, "black", 'b', 5, 0, false));
    row.emplace_back(new Knight(this, "black", 'n', 6, 0, false));
    row.emplace_back(new Rook(this, "black", 'r', 7, 0, false, false));

    theBoard.emplace_back(row);
    row.clear(); 
    
    //second row of the board. filled with pawns when initialized
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "black", 'p', i, 1, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // third row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, i, 2, true));
    }

    theBoard.emplace_back(row);
    row.clear();

    // fourth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, i, 3, true));
    }

    theBoard.emplace_back(row);
    row.clear();

    // fifth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, i, 4, true));
    }

    theBoard.emplace_back(row);
    row.clear();

    // sixth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, i, 5, true));
    }

    theBoard.emplace_back(row);
    row.clear();

    // seventh row. filled with pawns when initialized
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "white", 'P', i, 6, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // bottom row of the board. for the sake of pawn testing. leave it blank
    row.emplace_back(new Rook(this, "white", 'R', 0, 7, false, false));
    row.emplace_back(new Knight(this, "white", 'N', 1, 7, false));
    row.emplace_back(new Bishop(this, "white", 'B', 2, 7, false));
    row.emplace_back(new Queen(this, "white", 'Q', 3, 7, false));
    row.emplace_back(new King(this, "white", 'K', 4, 7, false, false));
    row.emplace_back(new Bishop(this, "white", 'B', 5, 7, false));
    row.emplace_back(new Knight(this, "white", 'N', 6, 7, false));
    row.emplace_back(new Rook(this, "white", 'R', 7, 7, false, false));

    theBoard.emplace_back(row);
    row.clear();


    this->attach(td);
    //this->attach(gd);
    this->notifyObservers();

}


void Board::setup() {

    td = new TextDisplay();

    /*
    theBoard.resize(8);
    for (int col = 0; col < 8; ++col) {
        theBoard[col].resize(8);
    }
    // initialize a board of blank pieces
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            theBoard[row][col] = new Piece(this, col, row, true);          
        }
    }
    */

    // initialize the board with the pieces
    vector<Piece*> row;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            row.emplace_back(new Piece(this, i, j, true));
        }
        theBoard.emplace_back(row);
        row.clear();
    }

    this->attach(td);
    this->notifyObservers();

    // done conditions
    bool kingInCheck = false;      // NEED TO ADD THIS
    bool kings = false;
    bool pawnLastRow = false;
    bool pawnFirstRow = false;

    // loop through theBoard and check for exactly one white king and one black king
    // if there is more than one of either or none, whiteKing = false or blackKing = false
    // if there is exactly one of each, whiteKing = true and blackKing = true
    
    
    // setup loop
    string op;    
    while (true) {
        cin >> op;
        if (op == "done") {
            int whiteKingCount = 0;
            int blackKingCount = 0;
            for (auto &row : theBoard) {
                for (auto &piece : row) {
                    if (piece->getSymbol() == 'K') {
                        whiteKingCount++;
                    } else if (piece->getSymbol() == 'k') {
                        blackKingCount++;
                    }
                }
            }

            if (whiteKingCount == 1 && blackKingCount == 1) {
                kings = true;
            } 
            else {
                cout << "Invalid setup. Need exactly 1 white king and 1 black king" << endl;
                continue;
            }

            // loop through theBoard and check for pawns in the first and last row
            // if there is a pawn in the first or last row, pawnFirstRow = true or pawnLastRow = true
            // if there is no pawn in the first or last row, pawnFirstRow = false and pawnLastRow = false
            // if there is a pawn in both the first and last row, pawnFirstRow = true and pawnLastRow = true
            for (auto &row : theBoard) {
                for (auto &piece : row) {
                    if (piece->getSymbol() == 'P') {
                        if (piece->getRow() == 0) {
                            pawnFirstRow = true;
                            cout << "Invalid. There is a pawn in the first row" << endl;
                        } else if (piece->getRow() == 7) {
                            pawnLastRow = true;
                            cout << "Invalid. There is a pawn in the last row" << endl;
                        }
                    } else if (piece->getSymbol() == 'p') {
                        if (piece->getRow() == 0) {
                            pawnFirstRow = true;
                            cout << "Invalid. There is a pawn in the first row" << endl;
                        } else if (piece->getRow() == 7) {
                            pawnLastRow = true;
                            cout << "Invalid. There is a pawn in the last row" << endl;
                        }
                    }
                }
            }

            if (!pawnFirstRow && !pawnLastRow && kings) {
                return;
            } else {
                continue;
            }
        } else if (op == "+") {
            char pieceType;
            string coord;
            cin >> pieceType >> coord;

            pair<int,int> move = p1->convertToCoord(coord);
            Piece *deletePiece = this->getPiece(move.first, move.second);
            Piece *newPiece = nullptr;

            // if pieceType is capital, call p1

            if (pieceType == 'K') {
                newPiece = new King(this, "white", 'K', move.first, move.second, false, false);
            } 
            else if (pieceType == 'k') {
                newPiece = new King(this, "black", 'k', move.first, move.second, false, false);
            }
            else if (pieceType == 'Q') {
                newPiece = new Queen(this, "white", 'Q', move.first, move.second, false);
            } 
            else if (pieceType == 'q') {
                newPiece = new Queen(this, "black", 'q', move.first, move.second, false);
            }
            else if (pieceType == 'N') {
                newPiece = new Knight(this, "white", 'N', move.first, move.second, false);
            } 
            else if (pieceType == 'n') {
                newPiece = new Knight(this, "black", 'n', move.first, move.second, false);
            }
            else if (pieceType == 'B') {
                newPiece = new Bishop(this, "white", 'B', move.first, move.second, false);
            } 
            else if (pieceType == 'b') {
                newPiece = new Bishop(this, "black", 'b', move.first, move.second, false);
            }
            else if (pieceType == 'R') {
                newPiece = new Rook(this, "white", 'R', move.first, move.second, false, false);
            } 
            else if (pieceType == 'r') {
                newPiece = new Rook(this, "black", 'r', move.first, move.second, false, false);
            }
            else if (pieceType == 'P') {
                newPiece = new Pawn(this, "white", 'P', move.first, move.second, false, false);
            } 
            else if (pieceType == 'p') {
                newPiece = new Pawn(this, "black", 'p', move.first, move.second, false, false);
            }
            delete deletePiece;
            setPiece(move.first, move.second, newPiece);

            this->notifyObservers();
            cout << *this->td; // print the board

        } else if (op == "-") {
            string coord;
            cin >> coord;
            pair<int,int> move = p1->convertToCoord(coord);

            // error handling for input here

            Piece *deletePiece = getPiece(move.first, move.second);
            Piece *newPiece = new Piece(this, move.first, move.second, true);

            delete deletePiece;
            setPiece(move.first, move.second, newPiece);

            this->notifyObservers();
            cout << *this->td; // print the board

        } else if (op == "=") {
            string colour;
            cin >> colour;
            if (colour == "white") {
                p1->setMyTurn(true);
                p2->setMyTurn(false);
            } else if (colour == "black") {
                p1->setMyTurn(false);
                p2->setMyTurn(true);
            }
        }
    }
}


// everytime you get piece, switch the x and y coordinates
// if coordinate is (4,6), then theBoard[6][4] is the piece
// thus, pass in getPiece(6,4) to get the piece at (4,6)
Piece *Board::getPiece(int x, int y) {
    return theBoard[x][y];
}

// same thing as getPiece
void Board::setPiece(int x, int y, Piece *p) {
    theBoard[x][y] = p;
}

void Board::changeTurn() {
    if (p1->getMyTurn()) {
        p2->setMyTurn(true);
    } else {
        p1->setMyTurn(true);
    }
}

Player *Board::getTurn() {
    if (p1->getMyTurn()) {
        return p1;
    } else {
        return p2;
    }
}

void Board::movePiece(vector<pair<int, int>> move) {
    pair<int, int> currentCoord = move[0];
    pair<int, int> newCoord = move[1];

    Piece *p = this->getPiece(currentCoord.first, currentCoord.second);
    Piece *temp = this->getPiece(newCoord.first, newCoord.second);

    bool inArray = false;
    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
    for (auto &coord : possibleMoves) {
        if (coord == newCoord) {
            inArray = true;
            break;
        }
    }
    if (inArray) {
        this->setPiece(newCoord.first, newCoord.second, p);
        this->setPiece(currentCoord.first, currentCoord.second, temp);
        p->setRow(newCoord.first);
        p->setCol(newCoord.second);
        temp->setRow(currentCoord.first);
        temp->setCol(currentCoord.second);
        temp->setBlank(true);
        this->notifyObservers();
        this->changeTurn();
    } 
}

void Board::isChecked() {
 
}

void Board::isCheckmated() {

}

void Board::isStalemated() {

}

ostream &operator<<(ostream &out, const Board &b) {
    out << *b.td;
    return out;
}


void Board::attach(Observer *o) {
    observers.emplace_back(o);
}

void Board::notifyObservers() {
    for (auto &ob : observers) {
        ob->notify(*this);
    }
}
