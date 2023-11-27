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
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 1));
    }

    theBoard.emplace_back(row);
    row.clear(); 
    
    //second row of the board. filled with pawns when initialized
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "black", 'p', i, 2, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // third row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 3));
    }

    theBoard.emplace_back(row);
    row.clear();

    // fourth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 4));
    }

    theBoard.emplace_back(row);
    row.clear();

    // fifth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 5));
    }

    theBoard.emplace_back(row);
    row.clear();

    // sixth row. should always be blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 6));
    }

    theBoard.emplace_back(row);
    row.clear();

    // seventh row. filled with pawns when initialized
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Pawn(this, "white", 'P', i, 7, false, false));
    }

    theBoard.emplace_back(row);
    row.clear();

    // bottom row of the board. for the sake of pawn testing. leave it blank
    for (int i = 0; i < 8; ++i) {
        row.emplace_back(new Piece(this, true, i, 8));
    }

    theBoard.emplace_back(row);
    row.clear();

    this->attach(td);
    //this->attach(gd);
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
        //p->setRow(newCoord.first);
        //p->setCol(newCoord.second);
        //p->setBlank(false);
        //temp->setRow(currentCoord.first);
        //temp->setCol(currentCoord.second);
        //temp->setBlank(true);
        this->notifyObservers();
        this->changeTurn();

    } else {
        cout << "Invalid move" << endl;
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
