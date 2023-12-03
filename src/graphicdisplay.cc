#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "graphicdisplay.h"
#include "window.h"

#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

using namespace std;

GraphicDisplay::GraphicDisplay() {
    dim = 800;
    cellDim = 80;

    theGDisplay = new Xwindow(1200, 800);

    // draw the title board and title
    // theGDisplay->fillRectangle(800, 0, 400, 250, Xwindow::Black);
    theGDisplay->fillRectangle(800, 0, 400, 800, Xwindow::Black);
    theGDisplay->fillRectangle(805, 5, 390, 240, Xwindow::Gray);
    theGDisplay->drawTitle();

    // create the top row of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        char c = 'A' + i - 1;
        theGDisplay->fillRectangle(cellDim * i, 0, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(cellDim * i + (cellDim / 2) - 6, (cellDim/2), string{c});
    }

    // create the right column of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        theGDisplay->fillRectangle(9 * cellDim, cellDim * i, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(9 * cellDim + (cellDim / 2), cellDim * i + (cellDim/2) + 6, to_string(i));
    }

    // create the bottom row of the board. 10 squares, 100 pixels each. all black
    for (int i = 9; i > 0; --i) {
        char c = 'A' + i - 1;
        theGDisplay->fillRectangle(cellDim * i, 9 * cellDim, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(cellDim * i + (cellDim / 2) - 6, 9 * cellDim + (cellDim / 2), string{c});
    }

    // create the left column of the board. 10 squares, 100 pixels each. all black
    for (int i = 9; i > 0; --i) {
        theGDisplay->fillRectangle(0, cellDim * i, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString((cellDim / 2), cellDim * i + (cellDim / 2) + 6, to_string(i));
    }

    // draw a black outline
    theGDisplay->fillRectangle(75, 75, 650, 650, Xwindow::Black);

    // draw the actual board, alternating off-white and green
    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            if ((row + col) % 2 == 0) {
                theGDisplay->fillRectangle(cellDim * col, cellDim * row, cellDim, cellDim, Xwindow::Khaki);
            } else {
                theGDisplay->fillRectangle(cellDim * col, cellDim * row, cellDim, cellDim, Xwindow::DarkOliveGreen);
            }
        }
    }
}

void GraphicDisplay::drawPiece(int row, int col, string symbol, int tileColour) {

    if (symbol == "P") {
        theGDisplay->drawBitMap(cellDim, col, row, whitePawn, tileColour);
    }
    else if (symbol == "p") {
        theGDisplay->drawBitMap(cellDim, col, row, blackPawn, tileColour);
    }
    else if (symbol == "K") {
        theGDisplay->drawBitMap(cellDim, col, row, whiteKing, tileColour);
    }
    else if (symbol == "k") {
        theGDisplay->drawBitMap(cellDim, col, row, blackKing, tileColour);
    }
    else if (symbol == "Q") {
        theGDisplay->drawBitMap(cellDim, col, row, whiteQueen, tileColour);
    }
    else if (symbol == "q") {
        theGDisplay->drawBitMap(cellDim, col, row, blackQueen, tileColour);
    }
    else if (symbol == "N") {
        theGDisplay->drawBitMap(cellDim, col, row, whiteKnight, tileColour);
    }
    else if (symbol == "n") {
        theGDisplay->drawBitMap(cellDim, col, row, blackKnight, tileColour);
    }
    else if (symbol == "B") {
        theGDisplay->drawBitMap(cellDim, col, row, whiteBishop, tileColour);
    }
    else if (symbol == "b") {
        theGDisplay->drawBitMap(cellDim, col, row, blackBishop, tileColour);
    }
    else if (symbol == "R") {
        theGDisplay->drawBitMap(cellDim, col, row, whiteRook, tileColour);
    }
    else if (symbol == "r") {
        theGDisplay->drawBitMap(cellDim, col, row, blackRook, tileColour);
    }
}

void GraphicDisplay::notify(Board &theBoard) {
    // iterate through the board and update the grid
    // use getPiece to get the piece at the position. 
    // if it is blank, then set the grid to be unchanged
    // if it is not blank, then set the grid to be the piece character

    if (drawnInitialState) {

        int oldRow = theBoard.gdCurrentCoord.first + 1;
        int oldCol = theBoard.gdCurrentCoord.second + 1;
        int newRow = theBoard.gdNewCoord.first + 1;
        int newCol = theBoard.gdNewCoord.second + 1;            

        int oldTileColour, newTileColour;

        ((oldRow + oldCol) % 2 == 0) ? oldTileColour = Xwindow::Khaki : oldTileColour = Xwindow::DarkOliveGreen;
        ((newRow + newCol) % 2 == 0) ? newTileColour = Xwindow::Khaki : newTileColour = Xwindow::DarkOliveGreen;

        Piece* oldPiece = theBoard.getPiece(oldRow-1, oldCol-1);
        Piece* newPiece = theBoard.getPiece(newRow-1, newCol-1);

        // change old coord
        if (oldPiece->isBlank()) {
            theGDisplay->fillRectangle(cellDim * oldCol, cellDim * oldRow, cellDim, cellDim, oldTileColour);
        } else {
            drawPiece(oldRow, oldCol, string{oldPiece->getSymbol()}, oldTileColour);
        }

        // change new coord
        if (newPiece->isBlank()) {
            theGDisplay->fillRectangle(cellDim * newCol, cellDim * newRow, cellDim, cellDim, newTileColour);
        } else {
            drawPiece(newRow, newCol, string{newPiece->getSymbol()}, newTileColour);
        }

    } else {

        for (int row = 1; row <= 8; ++row) {
            for (int col = 1; col <= 8; ++col) {
                Piece* curPiece = theBoard.getPiece(row-1, col-1);
                int tileColour;

                if ((row + col) % 2 == 0) {
                    tileColour = Xwindow::Khaki;
                } else {
                    tileColour = Xwindow::DarkOliveGreen;
                }

                if (curPiece->isBlank()) {
                    theGDisplay->fillRectangle(cellDim * col, cellDim * row, cellDim, cellDim, tileColour);
                    continue;
                }

                string symbol = string{curPiece->getSymbol()};
                drawPiece(row, col, symbol, tileColour);

            }
        }

        drawnInitialState = true;
    }

}

GraphicDisplay::~GraphicDisplay() {
    delete theGDisplay;
}
