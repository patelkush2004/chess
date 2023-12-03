#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_

#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "window.h"
#include "board.h"

class Board;

using namespace std;

class GraphicDisplay: public Observer {
        int dim = 800;
        int cellDim = 80;
        bool drawnInitialState = false;
        Xwindow *theGDisplay;
        
    public:
        GraphicDisplay();

        void notify(Board &theBoard) override;
        void drawPiece(int col, int row, string symbol, int tileColour);

        ~GraphicDisplay();
};

#endif
