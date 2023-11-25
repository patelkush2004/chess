#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"

using namespace std;

int main() {
    
    // read in the command "game white-player black-player"
    // ask: is the white player a human or a computer?
    // create a new player object based on the answer
    // it is white's turn, so call use setTurn() to set the turn to white
    // ask: is the black player a human or a computer?
    // create a new player object based on the answer
    // it is not the black's turn so call setTurn() to set the turn to false for black
    // then start the game

    // read in command

    Player *p1 = new Player("white");
    Plauer *p2 = new Player("black")
    Board b;
    b.init();
    cout << b;
    

    delete p1;
    delete p2;

}

