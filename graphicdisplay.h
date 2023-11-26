#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_

#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "window.h"

class Board;

using namespace std;

class GraphicDisplay: public Observer {
        Xwindow *theGDisplay;
    public:
        GraphicDisplay();

        void notify(Board &theBoard) override;

        ~GraphicDisplay();
};

#endif
