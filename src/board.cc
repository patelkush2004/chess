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
        vector <vector<Piece*>> theBoard = {};
        this->td = nullptr;
        this->gd = nullptr;
    }

// Destructor
Board::~Board() {
    for (auto &row : theBoard) {
        for (auto &piece : row) {
            delete piece;
        }
    }

    delete td;
    delete gd;
}

// Copy constructor
Board::Board(const Board &other) : 
    p1{other.p1}, p2{other.p2} {
        for (auto &row : other.theBoard) {
            vector<Piece*> pieceRow;
            Pawn *p = nullptr;
            Rook *r = nullptr;
            King *k = nullptr;
            for (auto &piece : row) {
                // if the piece has a symbol, create a new piece with the same symbol
                if (typeid(*piece) == typeid(Pawn) || typeid(*piece) == typeid(Rook) || typeid(*piece) == typeid(King)
                    || typeid(*piece) == typeid(Knight) || typeid(*piece) == typeid(Bishop) || typeid(*piece) == typeid(Queen)) {
                    if (piece->getSymbol() == 'P') {
                        p = dynamic_cast<Pawn*>(piece);
                        pieceRow.emplace_back(new Pawn(this, "white", 'P', p->getRow(), p->getCol(), p->isBlank(), p->getMoved()));
                    } else if (piece->getSymbol() == 'p') {
                        p = dynamic_cast<Pawn*>(piece);
                        pieceRow.emplace_back(new Pawn(this, "black", 'p', p->getRow(), p->getCol(), p->isBlank(), p->getMoved()));
                    } else if (piece->getSymbol() == 'R') {
                        r = dynamic_cast<Rook*>(piece);
                        pieceRow.emplace_back(new Rook(this, "white", 'R', r->getRow(), r->getCol(), r->isBlank(), r->getMoved()));
                    } else if (piece->getSymbol() == 'r') {
                        r = dynamic_cast<Rook*>(piece);
                        pieceRow.emplace_back(new Rook(this, "black", 'r', r->getRow(), r->getCol(), r->isBlank(), r->getMoved()));
                    } else if (piece->getSymbol() == 'N') {
                        pieceRow.emplace_back(new Knight(this, "white", 'N', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'n') {
                        pieceRow.emplace_back(new Knight(this, "black", 'n', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'B') {
                        pieceRow.emplace_back(new Bishop(this, "white", 'B', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'b') {
                        pieceRow.emplace_back(new Bishop(this, "black", 'b', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'Q') {
                        pieceRow.emplace_back(new Queen(this, "white", 'Q', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'q') {
                        pieceRow.emplace_back(new Queen(this, "black", 'q', piece->getRow(), piece->getCol(), piece->isBlank()));
                    } else if (piece->getSymbol() == 'K') {
                        k = dynamic_cast<King*>(piece);
                        pieceRow.emplace_back(new King(this, "white", 'K', k->getRow(), k->getCol(), k->isBlank(), k->getMoved()));
                    } else if (piece->getSymbol() == 'k') {
                        k = dynamic_cast<King*>(piece);
                        pieceRow.emplace_back(new King(this, "black", 'k', k->getRow(), k->getCol(), k->isBlank(), k->getMoved()));
                    }
                } else {
                    pieceRow.emplace_back(new Piece(this, piece->getRow(), piece->getCol(), piece->isBlank()));
                }
            }
            this->theBoard.emplace_back(pieceRow);
            pieceRow.clear();
        }
        this->td = nullptr;
        this->gd = nullptr;
    }

void Board::init() { // MOVEMENT NOT WORKING AFTER INIT COMPLETE
    td = new TextDisplay();
    gd = new GraphicDisplay();

    vector<Piece*> pieceRow;

    // top row of the board. for the sake of pawn testing. leave it blank
    pieceRow.emplace_back(new Rook(this, "black", 'r', 0, 0, false, false));
    pieceRow.emplace_back(new Knight(this, "black", 'n', 0, 1, false));
    pieceRow.emplace_back(new Bishop(this, "black", 'b', 0, 2, false));
    pieceRow.emplace_back(new Queen(this, "black", 'q', 0, 3, false));
    pieceRow.emplace_back(new King(this, "black", 'k', 0, 4, false, false));
    pieceRow.emplace_back(new Bishop(this, "black", 'b', 0, 5, false));
    pieceRow.emplace_back(new Knight(this, "black", 'n', 0, 6, false));
    pieceRow.emplace_back(new Rook(this, "black", 'r', 0, 7, false, false));

    theBoard.emplace_back(pieceRow);
    pieceRow.clear(); 
    
    //second row of the board. filled with pawns when initialized
    for (int col = 0; col < 8; ++col) {
        pieceRow.emplace_back(new Pawn(this, "black", 'p', 1, col, false, false));
    }

    theBoard.emplace_back(pieceRow);
    pieceRow.clear();

    // third to sixth row of the board. filled with blank pieces when initialized
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; ++col) {
            pieceRow.emplace_back(new Piece(this, row, col, true));
        }
        theBoard.emplace_back(pieceRow);
        pieceRow.clear();
    }
    
    // seventh row. filled with pawns when initialized
    for (int col = 0; col < 8; ++col) {
        pieceRow.emplace_back(new Pawn(this, "white", 'P', 6, col, false, false));
    }

    theBoard.emplace_back(pieceRow);
    pieceRow.clear();

    // bottom row of the board. for the sake of pawn testing. leave it blank
    pieceRow.emplace_back(new Rook(this, "white", 'R', 7, 0, false, false));
    pieceRow.emplace_back(new Knight(this, "white", 'N', 7, 1, false));
    pieceRow.emplace_back(new Bishop(this, "white", 'B', 7, 2, false));
    pieceRow.emplace_back(new Queen(this, "white", 'Q', 7, 3, false));
    pieceRow.emplace_back(new King(this, "white", 'K', 7, 4, false, false));
    pieceRow.emplace_back(new Bishop(this, "white", 'B', 7, 5, false));
    pieceRow.emplace_back(new Knight(this, "white", 'N', 7, 6, false));
    pieceRow.emplace_back(new Rook(this, "white", 'R', 7, 7, false, false));

    theBoard.emplace_back(pieceRow);
    pieceRow.clear();

    this->attach(td);
    this->attach(gd);
    this->notifyObservers();
}

void Board::setup() {   // MOVEMENT NOT WORKING AFTER SETUP COMPLETE
    td = new TextDisplay();
    gd = new GraphicDisplay();

    // initialize the board with blank pieces
    vector<Piece*> pieceRow;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            pieceRow.emplace_back(new Piece(this, row, col, true));
        }
        theBoard.emplace_back(pieceRow);
        pieceRow.clear();
    }

    this->attach(td);
    this->attach(gd);
    this->notifyObservers();

    // loop through theBoard and check for exactly one white king and one black king
    // loop through theBoard and check for pawns in the first and last row
    // if there is a pawn in the first or last row, pawnFirstRow = true or pawnLastRow = true
    // loop through theBoard and check if either king is in check

    // done conditions
    bool kings = false;
    bool pawnLastRow = false;
    bool pawnFirstRow = false;
    
    // setup loop
    string cmd;    
    while (true) {
        cin >> cmd;
        if (cmd == "done") {

            // loop through theBoard and check for exactly one white king and one black king
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
            for (int col = 0; col < 8; ++col) {
                Piece *p1 = this->getPiece(0, col);
                Piece *p2 = this->getPiece(7, col);
                if (p1->getSymbol() == 'P') {
                    pawnFirstRow = true;
                } else if (p2->getSymbol() == 'P') {
                    pawnLastRow = true;
                }
            }

            if (pawnFirstRow) {
                cout << "Invalid setup. There is a pawn in the first row" << endl;
                continue;
            }
            if (pawnLastRow) {
                cout << "Invalid setup. There is a pawn in the last row" << endl;
                continue;
            }

            // check if either king is in check
            bool whiteKingInCheck = false;
            bool blackKingInCheck = false;
            vector<pair<int, int>> whitePossibleMoves;
            vector<pair<int, int>> blackPossibleMoves;
            pair<int, int> whiteKingCoord;
            pair<int, int> blackKingCoord;

            // loop through theBoard and get all the possible moves for each piece and each team
            for (auto &row : theBoard) {
                for (auto &piece : row) {
                    if (piece->getTeam() == "white" && piece->isBlank() == false) {
                        vector<pair<int, int>> possibleMoves = piece->calculatePossibleMoves();
                        for (auto &coord : possibleMoves) {
                            whitePossibleMoves.emplace_back(coord);
                        }
                    } else if (piece->getTeam() == "black" && piece->isBlank() == false) {
                        vector<pair<int, int>> possibleMoves = piece->calculatePossibleMoves();
                        for (auto &coord : possibleMoves) {
                            blackPossibleMoves.emplace_back(coord);
                        }
                    }
                }
            }

            // get the coordinates of the kings
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8 ; col++) {
                    Piece *p = this->getPiece(row, col);
                    if (p->getSymbol() == 'K') {
                        whiteKingCoord = {row, col};
                    } else if (p->getSymbol() == 'k') {
                        blackKingCoord = {row, col};
                    }
                }
            }

            // check if white king is in check
            for (auto &coord : blackPossibleMoves) {
                if (coord == whiteKingCoord) {
                    whiteKingInCheck= true;
                    cout << "Invalid. White king is in check" << endl;
                    continue;
                }
            }

            // check if black king is in check
            for (auto &coord : whitePossibleMoves) {
                if (coord == blackKingCoord) {
                    blackKingInCheck = true;
                    cout << "Invalid. Black king is in check" << endl;
                    continue;
                }
            }

            if (!pawnFirstRow && !pawnLastRow && kings && !whiteKingInCheck && !blackKingInCheck) {
                return;
            } else {
                continue;
            }

        } else if (cmd == "+") {
            char pieceType;
            string coord;
            cin >> pieceType >> coord;

            pair<int,int> move = p1->convertToCoord(coord);

            Piece *deletePiece = this->getPiece(move.first, move.second);
            Piece *newPiece = nullptr;

            // make the new piece
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

        } else if (cmd == "-") {
            string coord;
            cin >> coord;
            pair<int,int> move = p1->convertToCoord(coord);

            Piece *deletePiece = getPiece(move.first, move.second);
            Piece *newPiece = new Piece(this, move.first, move.second, true);

            delete deletePiece;
            this->setPiece(move.first, move.second, newPiece);

            this->gdCurrentCoord = {move.first, move.second};
            this->gdNewCoord = {move.first, move.second};

            this->notifyObservers();
            cout << *this->td; // print the board

        } else if (cmd == "=") {
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

Piece *Board::getPiece(int row, int col) {
    return theBoard[row][col];
}

void Board::setPiece(int row, int col, Piece *p) {
    theBoard[row][col] = p;
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

void Board::movePiece(vector<pair<int, int>> move) { // FIX THIS AND CALCULATE POSSIBLE MOVES FOR ALL PIECES. USE THE CASTLING EXAMPLE
    // the current piece is at move[0], the new piece is at move[1]

    pair<int, int> currentCoord = move[0];
    pair<int, int> newCoord = move[1];

    // to check if the current piece has moved
    bool hasMovedFieldP = false;
    bool hasMovedFieldR = false;
    bool hasMovedFieldK = false;

    // current piece
    Piece *p = this->getPiece(currentCoord.first, currentCoord.second); 

    // check if the current player is moving their own piece
    if (p1->getMyTurn()) {
        if (p->getTeam() != "white") {
            //cout << "Invalid Move. Move your own piece" << endl;
            return;
        }
    } else if (p2->getMyTurn()) {
        if (p->getTeam() != "black") {
            //cout << "Invalid Move. Move your own piece" << endl;
            return;
        }
    }

    // casting the piece to its actual type if it has moved field
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
    // piece that current piece is swapping with
    Piece *temp = this->getPiece(newCoord.first, newCoord.second);

    // check if the current piece can move to the new coord
    bool inArray = false;
    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
    for (auto &coord : possibleMoves) {
        if (coord == newCoord) {
            inArray = true;
            break;
        }
    }

    bool castling = false;

    if (p->getSymbol() == 'K' || p->getSymbol() == 'k') {
        if (abs(currentCoord.second - newCoord.second) == 2) {
            castling = true;  
        }
    }


    if (inArray && !castling) {
        // castling. if king is move 2, skip the rest of the code in this function

        this->setPiece(newCoord.first, newCoord.second, p);
        this->setPiece(currentCoord.first, currentCoord.second, temp);

        // if the same player's king is in check after the move,
        // then the move is invalid
        // switch is back
        this->isChecked();
        if (p1->getMyTurn()) {
            if (p1->getIsCheck()) {
                this->setPiece(currentCoord.first, currentCoord.second, p);
                this->setPiece(newCoord.first, newCoord.second, temp);
                return;
            }
        } else if (p2->getMyTurn()) {
            if (p2->getIsCheck()) {
                this->setPiece(currentCoord.first, currentCoord.second, p);
                this->setPiece(newCoord.first, newCoord.second, temp);
                return;
            }
        }

        // pawn promotion
        if (this->getPiece(newCoord.first, newCoord.second)->getSymbol() == 'P' && newCoord.first == 0) {
            if (!p1->getIsCpu()) {
            string newPiece; // new piece symbol
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
            }
            else {
                Piece *newQueen = new Queen(this, "white", 'Q', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newQueen);
            }
        } else if (this->getPiece(newCoord.first, newCoord.second)->getSymbol() == 'p' && newCoord.first == 7) {
            if (!p2->getIsCpu()) {
                string newPiece; // new piece symbol
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
            else {
                Piece *newQueen = new Queen(this, "black", 'q', newCoord.first, newCoord.second, false);
                delete this->getPiece(newCoord.first, newCoord.second);
                this->setPiece(newCoord.first, newCoord.second, newQueen);
            }
        }

        p->setRow(newCoord.first);
        p->setCol(newCoord.second);
        temp->setRow(currentCoord.first);
        temp->setCol(currentCoord.second);
        temp->setBlank(true);

        // setting moved to true
        if (hasMovedFieldP) {
            piece->setMoved(true);
        } else if (hasMovedFieldR) {
            piece2->setMoved(true);
        } else if (hasMovedFieldK) {
            piece3->setMoved(true);
        }

        // notify observers
        this->gdCurrentCoord = currentCoord;
        this->gdNewCoord = newCoord;

        this->changeTurn();
        // cout << *this->td;
        // boardStates.pop();
        // vector<vector<string>> latest = boardStates.top();

        // for (int row = 0; row < 8; ++row) {
        //     for (int col = 0; col < 8; ++col) {
        //         cout << latest[row][col] << " ";
        //     }
        //     cout << endl;
        // }

        // applyState(latest);
        // notifyObservers();

        return;
    } 

    // castling
    if (p->getSymbol() == 'K' && (currentCoord == make_pair(7,4) && newCoord == make_pair(7,6))) {
        // white king moves right
        Piece *castlePiece = this->getPiece(7,7);
        bool rookMoved = false;
        if (castlePiece->getSymbol() == 'R') {
            Rook *castlePieceRook = dynamic_cast<Rook*>(castlePiece);
            rookMoved = castlePieceRook->getMoved();
        }
        else {
            return;
        }
        Piece *rookTemp = this->getPiece(7,5);
        if (piece3->getMoved() == false && rookMoved == false) {
            this->setPiece(newCoord.first, newCoord.second, p);
            this->setPiece(currentCoord.first, currentCoord.second, temp);
            this->setPiece(7,5,castlePiece);
            this->setPiece(7,7,rookTemp);
            this->isChecked();
            if (p1->getMyTurn()) {
                if (p1->getIsCheck()) {
                    this->setPiece(currentCoord.first, currentCoord.second, p);
                    this->setPiece(newCoord.first, newCoord.second, temp);
                    this->setPiece(7,7,castlePiece);
                    this->setPiece(7,5,rookTemp);
                    return;
                }
            }
            p->setRow(newCoord.first);
            p->setCol(newCoord.second);
            temp->setRow(currentCoord.first);
            temp->setCol(currentCoord.second);
            castlePiece->setRow(7);
            castlePiece->setCol(5);
            rookTemp->setRow(7);
            rookTemp->setCol(7);
        }
        this->gdCurrentCoord = make_pair(7,4);
        this->gdNewCoord = make_pair(7,6);

        this->gdCurrentCoord = make_pair(7,7);
        this->gdNewCoord = make_pair(7,5);
        this->changeTurn();
        return;
    }
    else if (p->getSymbol() == 'K' && (currentCoord == make_pair(7,4) && newCoord == make_pair(7,2))) {
        // white king moves right
        Piece *castlePiece = this->getPiece(7,0);
        bool rookMoved = false;
        if (castlePiece->getSymbol() == 'R') {
            Rook *castlePieceRook = dynamic_cast<Rook*>(castlePiece);
            rookMoved = castlePieceRook->getMoved();
        }
        else {
            return;
        }
        Piece *rookTemp = this->getPiece(7,3);
        if (piece3->getMoved() == false && rookMoved == false) {
            this->setPiece(newCoord.first, newCoord.second, p);
            this->setPiece(currentCoord.first, currentCoord.second, temp);
            this->setPiece(7,3,castlePiece);
            this->setPiece(7,0,rookTemp);

            // if castling causes the king to be in check, then the move is invalid
            this->isChecked();
            if (p1->getMyTurn()) {
                if (p1->getIsCheck()) {
                    this->setPiece(currentCoord.first, currentCoord.second, p);
                    this->setPiece(newCoord.first, newCoord.second, temp);
                    this->setPiece(7,0,castlePiece);
                    this->setPiece(7,3,rookTemp);
                    return;
                }
            }
            p->setRow(newCoord.first);
            p->setCol(newCoord.second);
            temp->setRow(currentCoord.first);
            temp->setCol(currentCoord.second);
            castlePiece->setRow(7);
            castlePiece->setCol(3);
            rookTemp->setRow(7);
            rookTemp->setCol(0);
        }
        this->gdCurrentCoord = make_pair(7,4);
        this->gdNewCoord = make_pair(7,2);

        this->gdCurrentCoord = make_pair(7,0);
        this->gdNewCoord = make_pair(7,3);
        this->changeTurn();
        return;
    }
    else if (p->getSymbol() == 'k' && (currentCoord == make_pair(0,4) && newCoord == make_pair(0,6))) {
        // white king moves right
        Piece *castlePiece = this->getPiece(0,7);
        bool rookMoved = false;
        if (castlePiece->getSymbol() == 'r') {
            Rook *castlePieceRook = dynamic_cast<Rook*>(castlePiece);
            rookMoved = castlePieceRook->getMoved();
        }
        else {
            return;
        }
        Piece *rookTemp = this->getPiece(0,5);
        if (piece3->getMoved() == false && rookMoved == false) {
            this->setPiece(newCoord.first, newCoord.second, p);
            this->setPiece(currentCoord.first, currentCoord.second, temp);
            this->setPiece(0,5,castlePiece);
            this->setPiece(0,7,rookTemp);

            this->isChecked();
            if (p1->getMyTurn()) {
                if (p1->getIsCheck()) {
                    this->setPiece(currentCoord.first, currentCoord.second, p);
                    this->setPiece(newCoord.first, newCoord.second, temp);
                    this->setPiece(0,7,castlePiece);
                    this->setPiece(0,5,rookTemp);
                    return;
                }
            }
            p->setRow(newCoord.first);
            p->setCol(newCoord.second);
            temp->setRow(currentCoord.first);
            temp->setCol(currentCoord.second);
            castlePiece->setRow(0);
            castlePiece->setCol(5);
            rookTemp->setRow(0);
            rookTemp->setCol(7);
        }
        this->gdCurrentCoord = make_pair(0,4);
        this->gdNewCoord = make_pair(0,6);

        this->gdCurrentCoord = make_pair(0,7);
        this->gdNewCoord = make_pair(0,5);
        this->changeTurn();
        return;
    }
    else if (p->getSymbol() == 'k' && (currentCoord == make_pair(0,4) && newCoord == make_pair(0,2))) {
        // white king moves right
        Piece *castlePiece = this->getPiece(0,0);
        bool rookMoved = false;
        if (castlePiece->getSymbol() == 'r') {
            Rook *castlePieceRook = dynamic_cast<Rook*>(castlePiece);
            rookMoved = castlePieceRook->getMoved();
        }
        else {
            return;
        }
        Piece *rookTemp = this->getPiece(0,3);
        if (piece3->getMoved() == false && rookMoved == false) {
            this->setPiece(newCoord.first, newCoord.second, p);
            this->setPiece(currentCoord.first, currentCoord.second, temp);
            this->setPiece(0,3,castlePiece);
            this->setPiece(0,0,rookTemp);

            this->isChecked();
            if (p1->getMyTurn()) {
                if (p1->getIsCheck()) {
                    this->setPiece(currentCoord.first, currentCoord.second, p);
                    this->setPiece(newCoord.first, newCoord.second, temp);
                    this->setPiece(0,0,castlePiece);
                    this->setPiece(0,3,rookTemp);
                    return;
                }
            }
            p->setRow(newCoord.first);
            p->setCol(newCoord.second);
            temp->setRow(currentCoord.first);
            temp->setCol(currentCoord.second);
            castlePiece->setRow(0);
            castlePiece->setCol(3);
            rookTemp->setRow(0);
            rookTemp->setCol(0);
        }
        this->gdCurrentCoord = make_pair(0,4);
        this->gdNewCoord = make_pair(0,2);

        this->gdCurrentCoord = make_pair(0,0);
        this->gdNewCoord = make_pair(0,3);
        this->changeTurn();
        return;
    }

}

Player* Board::getP1() { 
    return p1; 
}

Player* Board::getP2() { 
    return p2; 
}

void Board::clearBoard() {
    for (auto &row : theBoard) {
        for (auto &piece : row) {
            delete piece;
        }
        row.clear();
    }
    theBoard.clear();
}

void Board::clearBoardStates() {
    while (!boardStates.empty()) {
        boardStates.pop();
    }
}

void Board::isChecked() {
 
    // if it is player 1's turn, check if white king is in check.
    // if it is player 2's turn, check if black king is in check.

    pair<int, int> whiteKingCoord;
    pair<int, int> blackKingCoord;


    // get the coordinates of the kings
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8 ; col++) {
            Piece *p = this->getPiece(row, col);
            if (p->getSymbol() == 'K') {
                whiteKingCoord = make_pair(row, col);
            } else if (p->getSymbol() == 'k') {
                blackKingCoord = make_pair(row, col);
            }
        }
    }


    // check if white king is in check
    // loop through theBoard and find the black pieces 
    // check if the white king is in its possible moves
    vector<pair<int, int>> whitePossibleMoves;
    vector<pair<int, int>> blackPossibleMoves;


    if (p1->getMyTurn()) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8 ; col++) {
                Piece *p = this->getPiece(row, col);
                if (p->getTeam() == "black" && !p->isBlank()) {
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
                return;
            }
        }
        p1->setCheck(false);

    }
    else if (p2->getMyTurn()) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8 ; col++) {
                Piece *p = this->getPiece(row, col);
                if (p->getTeam() == "white" && !p->isBlank()) {
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
                return;
            }
        }
        p2->setCheck(false);
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

    // copy the board
    Board copy = *this;
    if (p1->getMyTurn()) {
        currentPlayer = p1;
    } else {
        currentPlayer = p2;
    }

    if (!currentPlayer->getIsCheck()) {
        currentPlayer->setCheckmate(false);
        return;
    }


    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8 ; col++) {
            Piece *p = this->getPiece(row, col);
            if (p1->getMyTurn() && p1->getIsCheck()) {
                if (p->getTeam() == "white" && !p->isBlank()) {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();

                    for (auto &coord : possibleMoves) {
                        vector<pair<int, int>> move = {make_pair(row, col), coord};
                        copy.movePiece(move);

                        if (!copy.p1->getIsCheck()) {
                            currentPlayer->setCheckmate(false);
                            return;
                        }
                    }
                }
            }
            else if (p2->getMyTurn() && p2->getIsCheck()) {
                if (p->getTeam() == "black" && !p->isBlank()) {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
                    for (auto &coord : possibleMoves) {
                        vector<pair<int, int>> move = {make_pair(row, col), coord};
                        copy.movePiece(move);

                        if (!copy.p2->getIsCheck()) {
                            currentPlayer->setCheckmate(false);
                            return;
                        }
                    }
                }
            }
        }
    }
    currentPlayer->setCheckmate(true);
    return;
}

void Board::isStalemated() {
    // if the current player is not in check
    // check if the current player has any possible moves
    // go through all the pieces of the current player
    // check if any of them have any possible moves such that the king is not in check
    // if there are no possible moves, then the current player is stalemated

    Player *currentPlayer;

    // copy the board
    Board copy = *this;

    if (p1->getMyTurn()) {
        currentPlayer = p1;
    } else {
        currentPlayer = p2;
    }

    if (currentPlayer->getIsCheck()) {
        currentPlayer->setStalemate(false);
        return;
    }

    bool p1PrevState = p1->getMyTurn(), p2PrevState = p2->getMyTurn();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8 ; col++) {
            Piece *p = this->getPiece(row, col);
            if (p1->getMyTurn() && !p1->getIsCheck()) {
                // cout << "should not be running" << endl;
                if (p->getTeam() == "white" && !p->isBlank()) {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();

                    for (auto &coord : possibleMoves) {
                        vector<pair<int, int>> move = {make_pair(row, col), coord};
                        copy.movePiece(move);

                        if (!copy.p1->getIsCheck()) {
                            currentPlayer->setStalemate(false);
                            p1->setMyTurn(p1PrevState);
                            p2->setMyTurn(p2PrevState);
                            return;
                        }
                    }
                }
            }
            else if (p2->getMyTurn() && !p2->getIsCheck()) {
                if (p->getTeam() == "black" && !p->isBlank()) {
                    vector<pair<int, int>> possibleMoves = p->calculatePossibleMoves();
                    for (auto &coord : possibleMoves) {
                        vector<pair<int, int>> move = {make_pair(row, col), coord};
                        copy.movePiece(move);
                        if (!copy.p2->getIsCheck()) {
                            currentPlayer->setStalemate(false);
                            p1->setMyTurn(p1PrevState);
                            p2->setMyTurn(p2PrevState);
                            return;
                        }

                    }
                }
            }
        }
    }
    currentPlayer->setStalemate(true);
    return;
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

void Board::notifyGraphicObservers() {
    gd->notify(*this);
}

void Board::boardtoState() {

    vector<vector<string>> state = {};
    state.resize(8);

    for (int row = 0; row < 8; ++row) {
        state[row].resize(8);
    }
     
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece *p = this->getPiece(row, col);
            char symbol = p->getSymbol();

            string pieceName;
            // switch case to make a temp string based on the symbol
            // lower case for black team, uppercase for white team
            Pawn* pieceP = nullptr;
            Rook* pieceR = nullptr;
            King* pieceK = nullptr;

            if (p->isBlank()) {
                pieceName = "blank";
            } else if (symbol == 'P') {
                pieceName = "Pawn";
                // pieceP = dynamic_cast<Pawn*>(p);
                // pieceP->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::PawnType) {
                    pieceP = dynamic_cast<Pawn*>(p);
                    pieceP->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
                // p->getType() == PieceType::PawnType ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
            } else if (symbol == 'p') {
                pieceName = "pawn";
                // pieceP = dynamic_cast<Pawn*>(p); // CHANGE
                // pieceP->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::PawnType) {
                    pieceP = dynamic_cast<Pawn*>(p);
                    pieceP->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
            } else if (symbol == 'R') {
                pieceName = "Rook";
                // pieceR = dynamic_cast<Rook*>(p);
                // pieceR->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::RookType) {
                    pieceR = dynamic_cast<Rook*>(p);
                    pieceR->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
            } else if (symbol == 'r') {
                pieceName = "rook";
                // pieceR = dynamic_cast<Rook*>(p);
                // pieceR->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::RookType) {
                    pieceR = dynamic_cast<Rook*>(p);
                    pieceR->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
            } else if (symbol == 'N') {
                pieceName = "Knight";
            } else if (symbol == 'n') {
                pieceName = "knight";
            } else if (symbol == 'B') {
                pieceName = "Bishop";
            } else if (symbol == 'b') {
                pieceName = "bishop";
            } else if (symbol == 'Q') {
                pieceName = "Queen";
            } else if (symbol == 'q') {
                pieceName = "queen";
            } else if (symbol == 'K') {
                pieceName = "King";
                // pieceK = dynamic_cast<King*>(p);
                // pieceK->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::KingType) {
                    pieceK = dynamic_cast<King*>(p);
                    pieceK->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
            } else if (symbol == 'k') {
                pieceName = "king";
                // pieceK = dynamic_cast<King*>(p);
                // pieceK->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                if (p->getType() == PieceType::KingType) {
                    pieceK = dynamic_cast<King*>(p);
                    pieceK->getMoved() ? pieceName = pieceName + "T" : pieceName = pieceName + "F";
                } else {
                    pieceName = pieceName + "F";
                }
            } else {
                pieceName = "blank";
            }

            state[row][col] = pieceName;
        }
    }

    // cout << "SYMBOL PRINTING hellloooodsfnskdfjdlsfkjfsdlkfdjklsdjkljklsdfjkldsflkjdfsjkldfskjl" << endl;

    // Piece * tempPiece = this->getPiece(2, 0);

    // cout << tempPiece->getSymbol() << endl;

    // cout << "BOARD old Pushed: " << "\n" << endl;
    // for (int row = 0; row < 8; ++row) {
    //     for (int col = 0; col < 8; ++col) {
    //         cout << state[row][col] << " ";
    //     }
    //     cout << endl;
    // }

    boardStates.push(state);

}

void Board::applyState(vector<vector<string>> state) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {

            if (state[row][col] == "blank") {
                Piece *newPiece = new Piece(this, row, col, true);
                delete this->getPiece(row, col);
                this->setPiece(row, col, newPiece);
            } else if (isupper(state[row][col][0])) {
                // white piece
                if (state[row][col] == "PawnT") {
                    Piece *newPiece = new Pawn(this, "white", 'P', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "PawnF") {
                    Piece *newPiece = new Pawn(this, "white", 'P', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "RookT") {
                    Piece *newPiece = new Rook(this, "white", 'R', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "RookF") {
                    Piece *newPiece = new Rook(this, "white", 'R', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "KingT") {
                    Piece *newPiece = new King(this, "white", 'K', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "KingF") {
                    Piece *newPiece = new King(this, "white", 'K', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "Knight") {
                    Piece *newPiece = new Knight(this, "white", 'N', row, col, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "Bishop") {
                    Piece *newPiece = new Bishop(this, "white", 'B', row, col, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                }
            } else {
                // black piece
                if (state[row][col] == "pawnT") {
                    Piece *newPiece = new Pawn(this, "black", 'p', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "pawnF") {
                    Piece *newPiece = new Pawn(this, "black", 'p', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "rookT") {
                    Piece *newPiece = new Rook(this, "black", 'r', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "rookF") {
                    Piece *newPiece = new Rook(this, "black", 'r', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "kingT") {
                    Piece *newPiece = new King(this, "black", 'k', row, col, false, true);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "kingF") {
                    Piece *newPiece = new King(this, "black", 'k', row, col, false, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "knight") {
                    Piece *newPiece = new Knight(this, "black", 'n', row, col, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                } else if (state[row][col] == "bishop") {
                    Piece *newPiece = new Bishop(this, "black", 'b', row, col, false);
                    delete this->getPiece(row, col);
                    this->setPiece(row, col, newPiece);
                }
            }

        }
    }
}

void Board::reversePiece() {
    vector<vector<string>> latest = boardStates.top();
    boardStates.pop();

    // cout << "BEFORE" << endl;

    // cout << *this;

    applyState(latest);

    // cout << "BOARD: " << "\n" << endl;
    // for (int row = 0; row < 8; ++row) {
    //     for (int col = 0; col < 8; ++col) {
    //         cout << latest[row][col] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "AFTER" << endl;

    // cout << *this;
    
    // tempVar++;

    this->changeTurn();


}


string Board::arrayToFENSyntax(Board& b) {
    std::string fen;
    for (int row = 0; row < 8; ++row) {
        if (row > 0) {
            fen += '/';
        }

        int emptyCount = 0;
        for (int col = 0; col < 8; ++col) {
            Piece* piece = b.getPiece(row, col);
            char symbol = piece->getSymbol();

            if (piece->isBlank()) {
                ++emptyCount;
            } else {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += symbol;
            }
        }

        if (emptyCount > 0) {
            fen += std::to_string(emptyCount);
        }
    }

    return fen;
}



