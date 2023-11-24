#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "human.h"
#include "computer.h"
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
    string cmd; 
    cin >> cmd;

    char answer1;
    char answer2;

    // create all 4 possible players
    Player *p1;
    Player *p2; //MIGHT NEED TO DO CASTING IDK TO CHANGE TYPE   

    if (cmd == "game") {
        string one;
        string two;
        cin >> one >> two;

        // ask the user if any computer or human players
        if (one == "white-player" && two == "black-player") {
            cout << "Is player 1 human? (Y/N)" << endl;
            cin >> answer1;
            cout << "Is player 2 human? (Y/N)" << endl;
            cin >> answer2;
        }
    }

    if (answer1 == 'Y') {
        p1 = new Human ("white");
    }
    else {
        p1 = new Computer ("white");
    }


    if (answer2 == 'Y') {
        p2 = new Human ("white");
    }
    else {
        p2 = new Computer ("white");
    }

    while (true) {
        
    }



}

