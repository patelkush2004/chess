#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "graphicdisplay.h"
#include "window.h"

using namespace std;

GraphicDisplay::GraphicDisplay() {
    theGDisplay = new Xwindow(1000, 1000);

    // create the top row of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        char c = 'a' + i;
        theGDisplay->fillRectangle(100 * i, 0, 100, 100, Xwindow::Black);
        theGDisplay->drawString(100 * i + 50, 50, to_string(c));
    }

    // create the left column of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        theGDisplay->fillRectangle(0, 100 * i, 100, 100, Xwindow::Black);
        theGDisplay->drawString(50, 100 * i + 50, to_string(i));
    }

    // create the right column of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        theGDisplay->fillRectangle(900, 100 * i, 100, 100, Xwindow::Black);
        theGDisplay->drawString(950, 100 * i + 50, to_string(i));
    }

    // create the bottom row of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        char c = 'a' + i;
        theGDisplay->fillRectangle(100 * i, 900, 100, 100, Xwindow::White);
        theGDisplay->drawString(100 * i + 50, 950, to_string(c));
    }

    // draw the actual board. first and last swuare are black. rest are alternating green and white
    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            if ((i + j) % 2 == 0) {
                theGDisplay->fillRectangle(100 * i, 100 * j, 100, 100, Xwindow::White);
            } else {
                theGDisplay->fillRectangle(100 * i, 100 * j, 100, 100, Xwindow::Green);
            }
        }
    }
}

void GraphicDisplay::notify(Board &theBoard) {
    // iterate through the board and update the grid
    // use getPiece to get the piece at the position. 
    // if it is blank, then set the grid to be unchanged
    // if it is not blank, then set the grid to be the piece character

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9 ; j++) {
            if (theBoard.getPiece(i, j)->isBlank() == true) {
                continue;
            } else {
                theGDisplay->drawString(100 * i + 50, 100 * j + 50, to_string(theBoard.getPiece(i, j)->getSymbol()));
            }
        }
    }
}

GraphicDisplay::~GraphicDisplay() {
    delete theGDisplay;
}
