#include "board.h"
#include "piece.h"
#include "pawn.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

// Constructor
Board::Board(Player *p1, Player *p2) : 
    p1{p1}, p2{p2} {
        vector <vector<Piece*>> theBoard = {};
        this->td = nullptr;
        init();
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
    delete this;
}

// init creates the piece and places them on the board. 
// by placing them on the board, it simply sets the coordinates properly

void Board::init() {
    td = new TextDisplay();

    vector<Piece*> row;

    // top row of the board. for the sake of pawn testing. leave it blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 0));
    }

    theBoard.emplace_back(row);
    row.clear(); 
    
    //second row of the board. for the sake of pawn testing. fill it with white pawns
    // White pieces
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "white", 'P', i, 1, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // middle of the board. this should always be initialized with blank pieces
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 2));
    }

    theBoard.emplace_back(row);
    row.clear();

    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 3));
    }

    theBoard.emplace_back(row);
    row.clear();

    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 4));
    }

    theBoard.emplace_back(row);
    row.clear();

    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 5));
    }

    theBoard.emplace_back(row);
    row.clear();

    // third row of the board. for the sake of pawn testing. fill it with black pawns
    // Black pieces
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "black", 'p', i, 6, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // bottom row of the board. for the sake of pawn testing. leave it blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 7));
    }

    theBoard.emplace_back(row);
    row.clear();

    this->attach(td);
    this->notifyObservers();

}

Piece *Board::getPiece(int x, int y) {
    return theBoard[x][y];
}

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

/*
void Board::detach(Observer *o) {
    for (auto &ob : observers) {
        if (ob == o) {
            observers.erase(ob);
        }
    }
}
*/ // NOT NEEDED TBH

void Board::notifyObservers() {
    for (auto &ob : observers) {
        ob->notify(*this);
    }
}
