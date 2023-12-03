#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "textdisplay.h"

using namespace std;

int main() {

    Player *p1;
    Player *p2;

    string cmd;
    cin >> cmd;

    //bool setupDone = false;

    // create players
    if (cmd == "game") {
        string player1;
        string player2;
        cin >> player1 >> player2;

        if (player1 == "human") {
            p1 = new Human("white", false, true);
        } else {
            p1 = new Computer("white", true, true); 
        }

        if (player2 == "human") {
            p2 = new Human("black", false, false);
        } else {
            p2 = new Computer("black", true, false); 
        }
    }

    Board b (p1, p2);

    //cout << b;

    // game loop
    while (cin >> cmd) {

        //if (p1->getMyTurn()) {
         //   cout << "White's turn" << endl;
        //}
        //else {
        //    cout << "Black's turn" << endl;
        //}

        if (cmd == "setup") {
            b.setup();

            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
            }
            else {
                cout << "White Turn" << endl;
            }

            cout << b;

        }
        else if (cmd == "done") {
            b.init();
            cout << b;

            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
            }
            else {
                cout << "White Turn" << endl;
            }


        }

        if (cmd == "resign") { // resign CHANGE THIS UP TOO IF NEEDED
            break;
        }

        // make move
        if (cmd == "move" && !p1->getIsCpu() && p1->getMyTurn()) {
            // ADD CONDITION TO SEE IF VALID TEAM IS MOVING VALID PIECE 
            string current;
            string newCoord;
            cin >> current >> newCoord;
            vector<pair<int, int>> move = p1->makeMove(current, newCoord);
            b.movePiece(move);
            cout << b;

            if (p2->getIsCpu()) {
                cout << "Black Computer Turn" << endl;
            }
            else {
                cout << "Black Turn" << endl;
            }

            b.isChecked();
            if (p2->getIsCheck()) {
                cout << "Black is in check." << endl;
            }

            b.isCheckmated();
            if (p2->getIsCheckmate()) {
                cout << "Checkmate! White wins!" << endl;
                p1->updateScore();
                // MAKE THE GAME CONTINUE
            }
        }
        else if (cmd == "move" && p1->getIsCpu() && p1->getMyTurn()) {
            vector<pair<int, int>> move = p1->makeComputerMove(b);
            b.movePiece(move);
            cout << b;
            if (p2->getIsCpu()) {
                cout << "Black Computer Turn" << endl;
            }
            else {
                cout << "Black Turn" << endl;
            }

            b.isChecked();
            if (p2->getIsCheck()) {
                cout << "Black is in check." << endl;
            }

            b.isCheckmated();
            if (p2->getIsCheckmate()) {
                cout << "Checkmate! White wins!" << endl;
                p1->updateScore();
                // MAKE THE GAME CONTINUE
            }
        }
        else if (cmd == "move" && p2->getIsCpu() && p2->getMyTurn()) {
            vector<pair<int, int>> move = p2->makeComputerMove(b);
            b.movePiece(move);
            cout << b;
            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
            }
            else {
                cout << "White Turn" << endl;
            }

            b.isChecked();
            if (p1->getIsCheck()) {
                cout << "White is in check." << endl;
            }

            b.isCheckmated();
            if (p1->getIsCheckmate()) {
                cout << "Checkmate! Black wins!" << endl;
                p2->updateScore();
                // MAKE THE GAME CONTINUE
            }
        }
        else if (cmd == "move" && !p2->getIsCpu() && p2->getMyTurn()) {
            string current;
            string newCoord;
            cin >> current >> newCoord;
            vector<pair<int, int>> move = p2->makeMove(current, newCoord);
            b.movePiece(move);
            cout << b;
            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
            }
            else {
                cout << "White Turn" << endl;
            }

            b.isChecked();
            if (p2->getIsCheck()) {
                cout << "Blac is in check." << endl;
            }
            
            b.isCheckmated();
            if (p1->getIsCheckmate()) {
                cout << "Checkmate! Black wins!" << endl;
                p2->updateScore();
                // MAKE THE GAME CONTINUE
            }
        }

        if (cin.fail()) {
            break;
        }
    }
    
    delete p1;
    delete p2;

}

