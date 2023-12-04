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

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8 ; col++) {
            if (theBoard.getPiece(row, col)->isBlank()) {
                if((row + col) % 2 == 0) {
                    theDisplay[row][col] = '_';
                } else {
                    theDisplay[row][col] = ' ';
                }
            } else {
                theDisplay[row][col] = theBoard.getPiece(row, col)->getSymbol();
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
        out << 8 - i << " |";

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
