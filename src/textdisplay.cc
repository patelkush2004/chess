#include "textdisplay.h"
#include "board.h"

using namespace std;

TextDisplay::TextDisplay() {
    // initialize the grid

    for (int i = 0; i < 4; i++) {
        vector<char> row1 = {' ', '_', ' ', '_', ' ', '_', ' ', '_'};
        vector<char> row2 = {'_', ' ', '_', ' ', '_', ' ', '_', ' '};
        theDisplay.emplace_back(row1);
        theDisplay.emplace_back(row2);
    }
}

void TextDisplay::notify(Board &theBoard) {
    // iterate through the board and update the grid
    // use getPiece to get the piece at the position. 
    // if it is blank, then set the grid to be unchanged
    // if it is not blank, then set the grid to be the piece character

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 ; j++) {
            if (theBoard.getPiece(i, j)->isBlank()) {
                if((i + j) % 2 == 0) {
                    theDisplay[i][j] = '_';
                } else {
                    theDisplay[i][j] = ' ';
                }
            } else {
                theDisplay[i][j] = theBoard.getPiece(i, j)->getSymbol();
            }
        }
    }
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    // iterate through the grid and print out the grid

    // print out the top row
    out << "   ________" << endl;

    for (int i = 0; i < 8; i++) {
        // print out the row number
        out << i + 1 << " |";

        for (int j = 0; j < 8; j++) {
            out << td.theDisplay[i][j];
        }
        out << "|" << endl;
    }
    out << endl;

    // print out the bottom row
    out << "   abcdefgh" << endl;

    return out;
}
