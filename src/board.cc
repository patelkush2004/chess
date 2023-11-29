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

    Piece *p = this->getPiece(currentCoord.second, currentCoord.first);
    Piece *temp = this->getPiece(newCoord.second, newCoord.first);

    bool inArray = false;
    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
    for (auto &coord : possibleMoves) {
        if (coord == newCoord) {
            inArray = true;
            break;
        }
    }

    if (inArray) {
        this->setPiece(newCoord.second, newCoord.first, p);
        this->setPiece(currentCoord.second, currentCoord.first, temp);
        p->setRow(newCoord.second);
        p->setCol(newCoord.first);
        temp->setRow(currentCoord.second);
        temp->setCol(currentCoord.first);
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
