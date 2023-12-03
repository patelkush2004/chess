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

    delete td;
    delete gd;
}

// init creates the piece and places them on the board. 
// by placing them on the board, it simply sets the coordinates properly

void Board::init() {
    td = new TextDisplay();
    gd = new GraphicDisplay();

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
    this->attach(gd);
    this->notifyObservers();

}


void Board::setup() {

    td = new TextDisplay();
    gd = new GraphicDisplay();

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
    this->attach(gd);
    this->notifyObservers();

    // done conditions
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
            for (int i = 0; i < 8; ++i) {
                Piece *p1 = this->getPiece(0, i);
                Piece *p2 = this->getPiece(7, i);
                if (p1->getSymbol() == 'P') {
                    pawnFirstRow = true;
                } else if (p2->getSymbol() == 'P') {
                    pawnLastRow = true;
                }
            }

            if (pawnFirstRow) {
                cout << "Invalid setup. There is a pawn in the first row" << endl;
            }
            if (pawnLastRow) {
                cout << "Invalid setup. There is a pawn in the last row" << endl;
            }

            // check if either king is in check
            bool whiteKingInCheck = false;
            bool blackKingInCheck = false;
            vector<pair<int, int>> whitePossibleMoves;
            vector<pair<int, int>> blackPossibleMoves;

            for (auto &row : theBoard) {
                for (auto &piece : row) {
                    if (piece->getTeam() == "white") {
                        vector<pair<int, int>> possibleMoves = piece->calculatePossibleMoves();
                        for (auto &coord : possibleMoves) {
                            whitePossibleMoves.emplace_back(coord);
                        }
                    } else if (piece->getTeam() == "black") {
                        vector<pair<int, int>> possibleMoves = piece->calculatePossibleMoves();
                        for (auto &coord : possibleMoves) {
                            blackPossibleMoves.emplace_back(coord);
                        }
                    }
                }
            }

            pair<int, int> whiteKingCoord;
            pair<int, int> blackKingCoord;

            // get the coordinates of the kings
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8 ; j++) {
                    Piece *p = this->getPiece(i, j);
                    if (p->getSymbol() == 'K') {
                        whiteKingCoord = {i, j};
                    } else if (p->getSymbol() == 'k') {
                        blackKingCoord = {i, j};
                    }
                }
            }

            // check if white king is in check
            for (auto &coord : blackPossibleMoves) {
                if (coord == whiteKingCoord) {
                    whiteKingInCheck= true;
                    cout << "Invalid. White king is in check" << endl;
                }
            }

            // check if black king is in check
            for (auto &coord : whitePossibleMoves) {
                if (coord == blackKingCoord) {
                    blackKingInCheck = true;
                    cout << "Invalid. Black king is in check" << endl;
                }
            }


            if (!pawnFirstRow && !pawnLastRow && kings && !whiteKingInCheck && !blackKingInCheck) {
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
            this->setPiece(move.first, move.second, newPiece);

            this->gdCurrentCoord = {move.first, move.second};
            this->gdNewCoord = {move.first, move.second};

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
            this->setPiece(move.first, move.second, newPiece);

            this->gdCurrentCoord = {move.first, move.second};
            this->gdNewCoord = {move.first, move.second};

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
        p1->setMyTurn(false);
    } else {
        p1->setMyTurn(true);
        p2->setMyTurn(false);
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

    bool hasMovedFieldP = false;
    bool hasMovedFieldR = false;
    bool hasMovedFieldK = false;

    bool check1 = false;
    bool check2 = false;
    this->isChecked();

    if (p1->getMyTurn()) {
        if (p1->getIsCheck()) {
            check1 = true;
        }
    } else if (p2->getMyTurn()) {
        if (p2->getIsCheck()) {
            check2 = true;
        }
    }

    Piece *p = this->getPiece(currentCoord.first, currentCoord.second);

    Pawn *piece = nullptr;  
    Rook *piece2 = nullptr;
    King *piece3 = nullptr;
    if (typeid(*p) == typeid(Pawn)) {
        piece = dynamic_cast<Pawn*>(p); 
        hasMovedFieldP = true;
    } 
    else if (typeid(*p) == typeid(Rook)) {
        piece2 = dynamic_cast<Rook*>(p);
        hasMovedFieldR = true;
    }
    else if (typeid(*p) == typeid(King)) {
        piece3 = dynamic_cast<King*>(p);
        hasMovedFieldK = true;
    }
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

        // if the same player's king is still in check, then the move is invalid
        // switch is back
        this->isChecked();
        if (p1->getMyTurn() && check1) {
            if (p1->getIsCheck()) {
                this->setPiece(currentCoord.first, currentCoord.second, p);
                this->setPiece(newCoord.first, newCoord.second, temp);
                //cout << "Invalid move. White king is still in check" << endl;
                return;
            }
        } else if (p2->getMyTurn() && check2) {
            if (p2->getIsCheck()) {
                this->setPiece(currentCoord.first, currentCoord.second, p);
                this->setPiece(newCoord.first, newCoord.second, temp);
                //cout << "Invalid move. Black king is still in check" << endl;
                return;
            }
        }
        
        // pawn promotion
        if (this->getPiece(newCoord.first, newCoord.second)->getSymbol() == 'P' && newCoord.first == 0) {
            // prompt user for input
            // if input is valid, then create a new piece and set it to theBoard
            // delete the old piece
            // if input is invalid, then do nothing
            string newPiece;
            cin >> newPiece;
            if (newPiece == "Q") {
                Piece *newQueen = new Queen(this, "white", 'Q', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newQueen);
            } else if (newPiece == "N") {
                Piece *newKnight = new Knight(this, "white", 'N', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newKnight);
            } else if (newPiece == "B") {
                Piece *newBishop = new Bishop(this, "white", 'B', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newBishop);
            } else if (newPiece == "R") {
                Piece *newRook = new Rook(this, "white", 'R', newCoord.first, newCoord.second, false, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newRook);
            }
        } else if (this->getPiece(newCoord.first, newCoord.second)->getSymbol() == 'p' && newCoord.second == 7) {
            // prompt user for input
            // if input is valid, then create a new piece and set it to theBoard
            // delete the old piece
            // if input is invalid, then do nothing
            string newPiece;
            cin >> newPiece;
            if (newPiece == "q") {
                Piece *newQueen = new Queen(this, "black", 'q', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newQueen);
            } else if (newPiece == "n") {
                Piece *newKnight = new Knight(this, "black", 'n', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newKnight);
            } else if (newPiece == "b") {
                Piece *newBishop = new Bishop(this, "black", 'b', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newBishop);
            } else if (newPiece == "r") {
                Piece *newRook = new Rook(this, "black", 'r', newCoord.first, newCoord.second, false, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newRook);
            }
        }

        // castling

        // IF PIECE AT CURRENT COORD IS A KING AND HAS NOT MOVED, AND THE PIECE AT NEW COORD IS A ROOK AND HAS NOT MOVED
        // AND THE PIECE AT NEW COORD IS EMPTY, AND THE PIECE AT THE COORD BETWEEN THE KING AND ROOK IS EMPTY
        // AND THE KING IS NOT IN CHECK, AND THE KING WILL NOT BE IN CHECK AFTER THE MOVE, DO THE CASTLE SHIT

        p->setRow(newCoord.first);
        p->setCol(newCoord.second);
        temp->setRow(currentCoord.first);
        temp->setCol(currentCoord.second);
        temp->setBlank(true);

        if (hasMovedFieldP) {
            piece->setMoved(true);
        } else if (hasMovedFieldR) {
            piece2->setMoved(true);
        } else if (hasMovedFieldK) {
            piece3->setMoved(true);
        }

        this->gdCurrentCoord = currentCoord;
        this->gdNewCoord = newCoord;
        this->notifyObservers();
        this->changeTurn();
    } 
}

void Board::isChecked() {
    // if it is player 1's turn, check if white king is in check.
    // if it is player 2's turn, check if black king is in check.

    pair<int, int> whiteKingCoord;
    pair<int, int> blackKingCoord;

    // get the coordinates of the kings
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 ; j++) {
            Piece *p = this->getPiece(i, j);
            if (p->getSymbol() == 'K') {
                whiteKingCoord = {i, j};
            } else if (p->getSymbol() == 'k') {
                blackKingCoord = {i, j};
            }
        }
    }

    // check if white king is in check
    // loop through theBoard and find the black pieces 
    // check if the white king is in its possible moves
    vector<pair<int, int>> whitePossibleMoves;
    vector<pair<int, int>> blackPossibleMoves;

    if (p1->getMyTurn()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8 ; j++) {
                Piece *p = this->getPiece(i, j);
                if (p->getTeam() == "black") {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
                    for (auto &coord : possibleMoves) {
                        blackPossibleMoves.emplace_back(coord);
                    }
                }
            }
        }
        for (auto &coord : blackPossibleMoves) {
            if (coord == whiteKingCoord) {
                p1->setCheck(true);
                break;
            }
        }

    }
    else if (p2->getMyTurn()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8 ; j++) {
                Piece *p = this->getPiece(i, j);
                if (p->getTeam() == "white") {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
                    for (auto &coord : possibleMoves) {
                        whitePossibleMoves.emplace_back(coord);
                    }
                }
            }
        }
        for (auto &coord : whitePossibleMoves) {
            if (coord == blackKingCoord) {
                p2->setCheck(true);
                break;
            }
        }
    }
}

void Board::isCheckmated() {
    // check if the current player is in check
    // if the current player is in check, check if the current player has any possible moves
    // go through all the pieces of the current player
    // check if any of them have any possible moves such that the king is not in check
    // if there are no possible moves, then the current player is checkmated
    // if the current player is not in check, then the current player is not checkmated

    Player *currentPlayer;

    if (p1->getMyTurn()) {
        currentPlayer = p1;
    } else {
        currentPlayer = p2;
    }

    if (!currentPlayer->getIsCheck()) {
        currentPlayer->setCheckmate(false);
        return;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 ; j++) {
            Piece *p = this->getPiece(i, j);
            if (p->getTeam() == "white") {
                vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
                for (auto &coord : possibleMoves) {
                    vector<pair<int, int>> move = {make_pair(i, j), coord};
                    
                    // copy the board
                    Board *copy = new Board(p1, p2);
                    copy->theBoard = this->theBoard;
                    copy->movePiece(move);

                    // check if the king is still in check
                    copy->isChecked();
                    if (!copy->p1->getIsCheck()) {
                        currentPlayer->setCheckmate(false);
                        return;
                    }

                    //delete copy;
                }
            }
        }
    }
    currentPlayer->setCheckmate(true);
    return;

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
