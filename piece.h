#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Piece {
    Board *theBoard // Pointer to the board that the piece is on. the piece now has access to the board and can call its methods
    //vector<pair<int, int>> possibleMoves; no need to include this. instead what we can do is call the calculatePossibleMoves() method and it will return the possible moves
    string team;
    char symbol;
    int row, col;
    bool blank;

    public:
        //default constructor
        Piece(Board *theBoard, bool blank, int row, int col);
        Piece(Board *theBoard, string team, char symbol, int row, int col, bool blank); // Constructor
        ~Piece(); // Destructor
        void setRow(int row); // set's the row of the piece
        void setCol(int col); // set's the col of the piece
        void setBlank(bool blank); // if the piece is blank, it has been captured, do don't display it
        vector<pair<int, int>> calculatePossibleMoves() override; // calculates the possible moves of the piece
        string getTeam(); // returns the team of the piece
        char getSymbol(); // returns the symbol of the piece
        int getRow(); // returns the row of the piece
        int getCol(); // returns the col of the piece
        bool isBlank(); // if the piece is blank, it has been captured, do don't display it
};

#endif
