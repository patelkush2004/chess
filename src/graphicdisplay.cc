#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "graphicdisplay.h"
#include "window.h"

#include "player.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

using namespace std;

GraphicDisplay::GraphicDisplay() {

    theGDisplay = new Xwindow(1200, 800);

    // draw the title board and title
    theGDisplay->fillRectangle(0, 0, 1200, 800, Xwindow::White);
    theGDisplay->fillRectangle(800, 0, 400, 800, Xwindow::Black);
    theGDisplay->fillRectangle(805, 5, 390, 250, Xwindow::Gray);
    theGDisplay->fillRectangle(805, 260, 390, 535, Xwindow::Gray);
    theGDisplay->drawTitle();

    // TURN
    theGDisplay->fillRectangle(860, 340, 280, 50, Xwindow::White);

    // SCORE
    graphicScoreMsg(true, 0);
    graphicScoreMsg(false, 0);

    // CHECK
    graphicCheckMsg("");

    // create the top row of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        char c = 'A' + i - 1;
        theGDisplay->fillRectangle(cellDim * i, 0, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(cellDim * i + (cellDim / 2) - 6, (cellDim/2) + 6, string{c});
    }

    // create the right column of the board. 10 squares, 100 pixels each. all black
    for (int i = 0; i < 10; ++i) {
        int num = 9 - i;
        theGDisplay->fillRectangle(9 * cellDim, cellDim * i, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(9 * cellDim + (cellDim / 2) - 6, cellDim * i + (cellDim/2) + 6, to_string(num));
    }

    // create the bottom row of the board. 10 squares, 100 pixels each. all black
    for (int i = 9; i > 0; --i) {
        char c = 'A' + i - 1;
        theGDisplay->fillRectangle(cellDim * i, 9 * cellDim, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString(cellDim * i + (cellDim / 2) - 6, 9 * cellDim + (cellDim / 2) + 6, string{c});
    }

    // create the left column of the board. 10 squares, 100 pixels each. all black
    for (int i = 9; i > 0; --i) {
        int num = 9 - i;
        theGDisplay->fillRectangle(0, cellDim * i, cellDim, cellDim, Xwindow::Gray);
        if (i > 0 && i < 9) theGDisplay->drawString((cellDim / 2) - 6, cellDim * i + (cellDim / 2) + 6, to_string(num));
    }

    // draw a black outline
    theGDisplay->fillRectangle(75, 75, 650, 650, Xwindow::Black);

    // draw the actual board, alternating off-white and green
    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            if ((row + col) % 2 == 0) {
                theGDisplay->fillRectangle(cellDim * col, cellDim * row, cellDim, cellDim, Xwindow::Moccasin);
            } else {
                theGDisplay->fillRectangle(cellDim * col, cellDim * row, cellDim, cellDim, Xwindow::DarkOliveGreen);
            }
        }
    }
}

void GraphicDisplay::graphicTurnMsg(string colour, bool cpu) {
    theGDisplay->fillRectangle(860, 340, 280, 50, Xwindow::White);

    if (colour == "white" && cpu) {
        theGDisplay->drawString(890, 370, "White Computer Turn");
    } else if (colour == "white") {
       theGDisplay->drawString(940, 370, "White Turn"); 
    } else if (colour == "black" && cpu) {
        theGDisplay->drawString(890, 370, "Black Computer Turn");
    } else {
        theGDisplay->drawString(940, 370, "Black Turn"); 
    }
}

void GraphicDisplay::graphicScoreMsg(bool player1, int score) {
    theGDisplay->fillRectangle(860, 420, 280, 40, Xwindow::White);
    theGDisplay->drawString(970, 447, "Score");

    string spaces = string{"                        "};
    if (player1) {
        theGDisplay->fillRectangle(860, 470, 280, 50, Xwindow::White);
        string p1msg = "Player 1:" + spaces + to_string(score);
        theGDisplay->drawString(890, 500, p1msg);
    } else {
        theGDisplay->fillRectangle(860, 530, 280, 50, Xwindow::White);
        string p2msg = "Player 2:" + spaces + to_string(score);
        theGDisplay->drawString(890, 560, p2msg);
    }
}

void GraphicDisplay::graphicCheckMsg(string status="") {
    theGDisplay->fillRectangle(860, 650, 280, 50, Xwindow::White);
    if (status == "check") {
        theGDisplay->drawString(965, 680, "CHECK!");
    } else if (status == "checkmate") {
        theGDisplay->drawString(930, 680, "CHECKMATE!");
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

void GraphicDisplay::updateGraphicCheck(Board &theBoard, string symbol, string checkmate) {
    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            Piece* curPiece = theBoard.getPiece(row-1, col-1);
            if (string{curPiece->getSymbol()} == symbol) {
                if (checkmate == "checkmate") {
                    drawPiece(row, col, symbol, Xwindow::FireBrick);
                    graphicCheckMsg("checkmate");
                } else if (checkmate == "check"){
                    graphicCheckMsg("check");
                    drawPiece(row, col, symbol, Xwindow::LightCoral);
                }
                else {
                    int tileColour;
                    ((row + col) % 2 == 0) ? tileColour = Xwindow::Moccasin : tileColour = Xwindow::DarkOliveGreen;
                    drawPiece(row, col, symbol, tileColour);
                }
                // checkmate ? drawPiece(row, col, symbol, Xwindow::FireBrick) : drawPiece(row, col, symbol, Xwindow::LightCoral);
            }
        }
    }
}

void GraphicDisplay::notify(Board &theBoard) {
    // iterate through the board and update the grid
    // use getPiece to get the piece at the position. 
    // if it is blank, then set the grid to be unchanged
    // if it is not blank, then set the grid to be the piece character

    if (drawnInitialState) {

        if (theBoard.getP1()->getIsCheckmate()) {
            updateGraphicCheck(theBoard, "K", "checkmate"); 
            return;
        }

        else if (theBoard.getP1()->getIsCheck()) {
            updateGraphicCheck(theBoard, "K", "check");
        }

        else if (theBoard.getP2()->getIsCheckmate()) {
            updateGraphicCheck(theBoard, "k", "checkmate");
            return;
        }

        else if (theBoard.getP2()->getIsCheck()) {
            updateGraphicCheck(theBoard, "k", "check");
        }

        else {
            updateGraphicCheck(theBoard, "k", "none");
        }


        int oldRow = theBoard.gdCurrentCoord.first + 1;
        int oldCol = theBoard.gdCurrentCoord.second + 1;
        int newRow = theBoard.gdNewCoord.first + 1;
        int newCol = theBoard.gdNewCoord.second + 1;            

        int oldTileColour, newTileColour;

        ((oldRow + oldCol) % 2 == 0) ? oldTileColour = Xwindow::Moccasin : oldTileColour = Xwindow::DarkOliveGreen;
        ((newRow + newCol) % 2 == 0) ? newTileColour = Xwindow::Moccasin : newTileColour = Xwindow::DarkOliveGreen;

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
                    tileColour = Xwindow::Moccasin;
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
