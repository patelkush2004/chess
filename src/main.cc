#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"
#include "human.h"
#include "textdisplay.h"

using namespace std;

int main() {

    Player *p1;
    Player *p2;

    string cmd;
    cin >> cmd;

    bool setupDone = false;

    // create players
    if (cmd == "game") {
        string player1;
        string player2;
        cin >> player1 >> player2;

        if (player1 == "human") {
            p1 = new Human("white");
        } else {
            p1 = new Player("white"); // change this to computer after
        }

        if (player2 == "human") {
            p2 = new Human("black");
        } else {
            p2 = new Player("black"); // change this to computer after
        }
    }

    Board b (p1, p2);

    // game loop
    while (cin >> cmd) {

        if (cmd == "setup") {
            setupDone = true;
            b.setup();
        }

        if (!setupDone) {
            setupDone = true;
            b.init();
        }

        cout << b;

        if (cmd == "resign") { // resign CHANGE THIS UP TOO IF NEEDED
            break;
        }

        // make move
        if (cmd == "move") {

            // ADD CONDITION TO SEE IF VALID TEAM IS MOVING VALID PIECE 
            string current;
            string newCoord;
            cin >> current >> newCoord;
            vector<pair<int, int>> move = p1->makeMove(current, newCoord);
            b.movePiece(move);
            cout << b;
        }

        if (cin.fail()) {
            break;
        }
    }
    
    delete p1;
    delete p2;

}

