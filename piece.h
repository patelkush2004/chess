#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <string>
#include <iostream>
#include "board.h"

class Board;

using namespace std;

class Piece {
    Board *theBoard; // Pointer to the board that the piece is on. the piece now has access to the board and can call its methods
    //vector<pair<int, int>> possibleMoves; no need to include this. instead what we can do is call the calculatePossibleMoves() method and it will return the possible moves
    string team;
    char symbol;
    int x, y;
    bool blank;

    public:
        //default constructor
        Piece(Board *theBoard, int x, int y, bool blank);
        Piece(Board *theBoard, string team, char symbol, int x, int y, bool blank); // Constructor
        virtual ~Piece(); // Destructor
        void setRow(int row); // set's the row of the piece
        void setCol(int col); // set's the col of the piece
        void setBlank(bool blank); // if the piece is blank, it has been captured, do don't display it
        virtual vector<pair<int, int>> calculatePossibleMoves(); // calculates the possible moves of the piece
        string getTeam(); // returns the team of the piece
        char getSymbol(); // returns the symbol of the piece
        int getRow(); // returns the row of the piece
        int getCol(); // returns the col of the piece
        bool isBlank(); // if the piece is blank, it has been captured, do don't display it
        Board *getBoard(); // returns the board that the piece is on
};

#endif
