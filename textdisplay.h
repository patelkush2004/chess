#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <vector>
#include <string>
#include "observer.h"

class Board;

class TextDisplay: public Observer {
        std::vector<std::vector<char>> theDisplay;
    public:
        TextDisplay();
        void notify(Board &theBoard) override;
        ~TextDisplay();
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
