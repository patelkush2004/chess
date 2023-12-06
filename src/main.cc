#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "textdisplay.h"

class graphicDisplay;

using namespace std;

int main() {

    // create players. set the pointer to nullptr
    Player *p1 = nullptr; 
    Player *p2 = nullptr;

    bool resign = false;

    int level1 = 1;
    int level2 = 2;

    string cmd;
    cin >> cmd;

    // create specific players
    if (cmd == "game") {
        string player1;
        string player2;
        cin >> player1 >> player2;

        if (player1 == "human") {
            p1 = new Human("white", false, true);
        } 
        else if (player1 == "computer[1]" || player1 == "computer[2]" || player1 == "computer[3]" || player1 == "computer[4]" || player1 == "computer[5]") {
            p1 = new Computer("white", true, true);
            for (size_t i = 0; i < player1.size(); ++i) {
                if (player1[i] >= '0' && player1[i] <= '9') level1 = player1[i] - '0';
            }
        }

        if (player2 == "human") {
            p2 = new Human("black", false, true);
        } 
        else if (player2 == "computer[1]" || player2 == "computer[2]" || player2 == "computer[3]" || player2 == "computer[4]" || player2 == "computer[5]") {
            p2 = new Computer("black", true, true);
            for (size_t i = 0; i < player2.size(); ++i) {
                if (player2[i] >= '0' && player2[i] <= '9') level2 = player2[i] - '0';
            }
        }

    }


    Board b (p1, p2); // create board stack allocated

    // game loop
    while (cin >> cmd) {

        if (cmd == "setup") {
            b.setup();
            cout << b;

            // White player always goes first
            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("white", true);
            }
            else {
                cout << "White Turn" << endl;
                b.getGd()->graphicTurnMsg("white", false);
            }
        }
        else if (cmd == "done") {
            b.init();
            cout << b;

            if (p1->getIsCpu()) {
                cout << "White Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("white", true);
            }
            else {
                cout << "White Turn" << endl;
                b.getGd()->graphicTurnMsg("white", false);
            }
        }

        if (cmd == "resign") { // resign 
            if (p1->getMyTurn()) {
                cout << "Black wins!" << endl;
                p2->updateScore();
                b.getGd()->graphicScoreMsg("black", p2->getScore());
            } else {
                cout << "White wins!" << endl;
                p1->updateScore();
                b.getGd()->graphicScoreMsg("white", p1->getScore());
            }
            resign = true;
        }

        // make move
        if (cmd == "move" && !p1->getIsCpu() && p1->getMyTurn()) {

            b.notifyObservers();

            string current;
            string newCoord;
            cin >> current >> newCoord;
            vector<pair<int, int>> move = p1->makeMove(current, newCoord);
            b.movePiece(move);
            cout << b;

            if (p2->getIsCpu() && p2->getMyTurn()) {
                cout << "Black Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("black", true);
            }
            else if (p2->getMyTurn()){
                cout << "Black Turn" << endl;
                b.getGd()->graphicTurnMsg("black", false);
            }


            b.isChecked();
            b.notifyGraphicObservers();
          
            if (p2->getIsCheck()) {
                cout << "Black is in check." << endl;
                b.getGd()->graphicCheckMsg("check");
            }


            b.isCheckmated();
            b.notifyGraphicObservers();

            if (p2->getIsCheckmate()) {
                cout << "Checkmate! White wins!" << endl;
                p1->updateScore();
                b.getGd()->graphicScoreMsg(true, p1->getScore());
                b.getGd()->graphicCheckMsg("checkmate");
            }


            b.isStalemated();
            b.notifyGraphicObservers();

            if (p2->getIsStalemate()) {
                cout << "Stalemate! Draw!" << endl;

            }


        }
        else if (cmd == "move" && p1->getIsCpu() && p1->getMyTurn()) {

            b.notifyObservers();

            vector<pair<int, int>> move = p1->makeComputerMove(b, level1);
            b.movePiece(move);
            cout << b;
            if (p2->getIsCpu() && p2->getMyTurn()) {
                cout << "Black Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("black", true);
            }
            else if (p2->getMyTurn()){
                cout << "Black Turn" << endl;
                b.getGd()->graphicTurnMsg("black", false);
            }

            b.isChecked();
            b.notifyGraphicObservers();

            if (p2->getIsCheck()) {
                cout << "Black is in check." << endl;
                b.getGd()->graphicCheckMsg("check");
            }

            b.isCheckmated();
            b.notifyGraphicObservers();

            if (p2->getIsCheckmate()) {
                cout << "Checkmate! White wins!" << endl;
                p1->updateScore();
                b.getGd()->graphicScoreMsg("white", p1->getScore());
                b.getGd()->graphicCheckMsg("checkmate");
                // MAKE THE GAME CONTINUE
            }
            b.isStalemated();
            b.notifyGraphicObservers();

            if (p2->getIsStalemate()) {
                cout << "Stalemate! Draw!" << endl;
                //b.getGd()->graphicCheckMsg("checkmate"); FIX THIS
            }
        }
        else if (cmd == "move" && p2->getIsCpu() && p2->getMyTurn()) {

            b.notifyObservers();

            vector<pair<int, int>> move = p2->makeComputerMove(b, level2);
            b.movePiece(move);
            cout << b;
            if (p1->getIsCpu() && p1->getMyTurn()) {
                cout << "White Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("white", true);
            }
            else if (p1->getMyTurn()){
                cout << "White Turn" << endl;
                b.getGd()->graphicTurnMsg("white", false);
            }

            b.isChecked();
            b.notifyGraphicObservers();

            if (p1->getIsCheck()) {
                cout << "White is in check." << endl;
                b.getGd()->graphicCheckMsg("check");
            }

            b.isCheckmated();
            b.notifyGraphicObservers();

            if (p1->getIsCheckmate()) {
                cout << "Checkmate! Black wins!" << endl;
                p2->updateScore();
                b.getGd()->graphicScoreMsg("white", p2->getScore());
                b.getGd()->graphicCheckMsg("checkmate");
                // MAKE THE GAME CONTINUE
            }

            b.isStalemated();
            b.notifyGraphicObservers();

            if (p1->getIsStalemate()) {
                cout << "Stalemate! Draw!" << endl;
                //b.getGd()->graphicCheckMsg("checkmate"); FIX THIS
            }
        }
        else if (cmd == "move" && !p2->getIsCpu() && p2->getMyTurn()) {

            b.notifyObservers();

            string current;
            string newCoord;
            cin >> current >> newCoord;
            vector<pair<int, int>> move = p2->makeMove(current, newCoord);
            b.movePiece(move);
            cout << b;
            if (p1->getIsCpu() && p1->getMyTurn()) {
                cout << "White Computer Turn" << endl;
                b.getGd()->graphicTurnMsg("white", true);
            }
            else if (p1->getMyTurn()){
                cout << "White Turn" << endl;
                b.getGd()->graphicTurnMsg("white", false);
            }

            b.isChecked();
            b.notifyGraphicObservers();

            if (p1->getIsCheck()) {
                cout << "White is in check." << endl;
                b.getGd()->graphicCheckMsg("check");
            }
            
            b.isCheckmated();
            b.notifyGraphicObservers();

            if (p1->getIsCheckmate()) {
                cout << "Checkmate! Black wins!" << endl;
                p2->updateScore();
                b.getGd()->graphicScoreMsg("black", p2->getScore());
                b.getGd()->graphicCheckMsg("checkmate");
                // MAKE THE GAME CONTINUE
            }

            b.isStalemated();
            b.notifyGraphicObservers();

            if (p1->getIsStalemate()) {
                cout << "Stalemate! Draw!" << endl;
                //b.getGd()->graphicCheckMsg("checkmate"); FIX THIS
            }
        }

        if (p1->getIsCheckmate() || p2->getIsCheckmate() || p1->getIsStalemate() || p2->getIsStalemate() || resign) {
            cout << "Do you want to play again? (yes/no)" << endl;
            string answer;
            cin >> answer;
            if (answer == "yes") {

                int score1 = p1->getScore();
                int score2 = p2->getScore();

                p1->setCheck(false);
                p1->setCheckmate(false);
                p1->setStalemate(false);
                p2->setCheck(false);
                p2->setCheckmate(false);
                p2->setStalemate(false);
                p1->setScore(score1);
                p2->setScore(score2);

                p1->setMyTurn(true);
                p2->setMyTurn(false);

                // graphic display not showing the right score
                b.getGd()->graphicScoreMsg("white", p1->getScore());
                b.getGd()->graphicScoreMsg("black", p2->getScore());

                b.clearBoard();
                b.clearBoardStates();

                resign = false;
            }
            else if (answer == "no") {
                break;
            }
        }

        if (cin.fail()) {
            break;
        }
    }
    
    delete p1;
    delete p2;

}

