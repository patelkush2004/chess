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
